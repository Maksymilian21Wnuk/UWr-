#include "util.h"

// globals........

struct icmp header;
struct sockaddr_in recipient;
struct timeval tv;
fd_set descriptors;

int main(int argc, char *argv[])
{

    // check if properly written command and whether user is root

    if (getuid() != 0)
    {
        fprintf(stderr, "Root priveleges needed\n");
        exit(EXIT_FAILURE);
    }

    if (argc < 2)
    {
        fprintf(stderr, "Wrong usage of program, ip needed\n");
        exit(EXIT_FAILURE);
    }

    printf("traceroute to %s, 30 hops max: \n\n", argv[1]);

    // receiver manipulation
    recipient_init(argv[1]);

    // creating raw socket and error control
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0)
    {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    // data for select function
    select_util(sockfd);

    // data used to count time
    clock_t timers[3];
    clock_t time_average;

    // variables needed for receiving packet
    ssize_t packet_rec;

    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET];

    // variables needed in sending loop
    int ttl_num = 1;

    char sender_ip_str[20];
    int response = ACQUIRED_RESPONSE;
    int packet_num = 0;
    bool final_dest = false;
    // counting not responded routers, if equal not equal
    // to 3, print ??? 
    int not_responded_count = 0;

    // ttl num to 1
    setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl_num, sizeof(int));

    while (!final_dest && ttl_num < 30)
    {
        header_init(ttl_num);
        
        // send 3 continuous packets
        send_packet(sockfd, header, recipient);
        
        // receive 3 packets
        while (packet_num + not_responded_count != 3){
            select_util(sockfd);            
            timers[packet_num] = clock();
            
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);
            // if timeout, increment not responded number and receive again
            if (ready == 0){
                not_responded_count += 1;
                continue;
            }

            packet_rec = recvfrom(sockfd, buffer, IP_MAXPACKET, 0,
                                (struct sockaddr *)&sender, &sender_len);


            if (packet_rec == -1)
            {
                fprintf(stderr, "Recvfrom error: %s \n", strerror(errno));
            }

            // update time
            timers[packet_num] = clock() - timers[packet_num];

            // get type id seqnum in rec_info
            rec_info ri = get_rec_info(buffer);

            // If our reply is in destination,
            // check if pid is same, if yes,
            // we are in final destination
            if (ri.type == ICMP_ECHOREPLY)
            {
                if (ri.sender_id != getpid() || !was_last(ri.sender_seq, ttl_num)){
                    continue;
                }
                final_dest = true;
            }

            // every time packet is not in destination,
            // we should get ICMP_TIME_EXCEEDED,
            // in this block of code i check if
            // packet received belongs to process by checking
            // its id == pid, and checking seq number
            else if (ri.type == ICMP_TIME_EXCEEDED)
            {

                // if not pid of program, loop all over again
                if (ri.id != getpid() || !was_last(ri.seq, ttl_num))
                {
                    continue;
                }
            }
            else
            {
                continue;
            }

            // packet belonged to this process, move onto +1 packet num
            packet_num += 1;

        }

        if (not_responded_count > 0){
            response = NO_RESPONSE;
            if (not_responded_count < 3){
                response = NOT_EVERY_RESPONDED;
            }
        }

        // average time out of 3 packets sent
        time_average = (timers[0] + timers[1] + timers[2]) / 3.0;

        // TODO: PRINT UTIL
        // if no response from router, print ***
        if (response == NO_RESPONSE)
        {
            printf("%d ***\n", ttl_num);
        }

        else if (response == NOT_EVERY_RESPONDED){
            inet_ntop(
                AF_INET, &(sender.sin_addr),
                sender_ip_str, sizeof(sender_ip_str));

            printf("%d %s ???\n", ttl_num, sender_ip_str);
        }

        // router did respond, print ip and timer to sdout
        else
        {

            inet_ntop(
                AF_INET, &(sender.sin_addr),
                sender_ip_str, sizeof(sender_ip_str));

            printf("%d %s   %ldms\n", ttl_num, sender_ip_str, time_average);
        }

        // set jump up in ttls and jump one further
        ttl_num += 1;
        setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl_num, sizeof(int));

        // this really is important......
        // reseting select variables such as set and timevals
        packet_num = 0;
        not_responded_count = 0;
        response = ACQUIRED_RESPONSE;        
    }

    return 0;
}