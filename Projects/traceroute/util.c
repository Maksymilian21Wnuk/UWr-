#include "util.h"

// checksum from lectures
u_int16_t compute_icmp_checksum(const void *buff, int length)
{
    u_int32_t sum;
    const u_int16_t *ptr = buff;
    assert(length % 2 == 0);
    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;
    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t)(~(sum + (sum >> 16)));
}

// initializing the sender's header
void header_init(int ttl)
{
    header.icmp_type = ICMP_ECHO;
    header.icmp_hun.ih_idseq.icd_id = getpid();
    header.icmp_hun.ih_idseq.icd_seq = ttl << 2;
    header.icmp_code = 0;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum((u_int16_t *)&header, sizeof(header));
    return;
}

// initializing recipient with basic data
void recipient_init(char *ip_string)
{
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    inet_pton(AF_INET, ip_string, &recipient.sin_addr);
}

// manipulate select variables,
// important to do this in loop
void select_util(int sockfd)
{
    FD_ZERO(&descriptors);
    FD_SET(sockfd, &descriptors);
    tv.tv_sec = 1;
    tv.tv_usec = 0;
}

// function used in verifying if sequence number
// in received message is correct
bool was_last(int seq_num, int ttl)
{
    return ttl == seq_num >> 2;
}

// function that sends packet to recipient
// it returns whether the router respond
// function uses select in order to prevent active waiting
// in tv structure there is one second time limit
void send_packet(int sockfd, struct icmp header, struct sockaddr_in recipient)
{
    for (int i = 0; i < 3; i++){
        int check = sendto(sockfd, &header, sizeof(header), 0,
            (struct sockaddr *)&recipient, sizeof(recipient));
        
        if (check == -1){
            fprintf(stderr,"Error when sending packet: %s \n", strerror(errno));
        }
    }
}

// function to get id type and sequence number
// from receiver, its important to do this
// in order to identify if receiver
// belongs do this process
rec_info get_rec_info(u_int8_t *buffer)
{
    rec_info ri;

    struct ip *ip_header = (struct ip *)buffer;
    ssize_t ip_header_len = 4 * ip_header->ip_hl;

    u_int8_t *icmp_packet = buffer + ip_header_len;
    struct icmp *icmp_header = (struct icmp *)icmp_packet;

    ri.sender_id = icmp_header->icmp_hun.ih_idseq.icd_id;
    ri.sender_seq = icmp_header->icmp_hun.ih_idseq.icd_seq;

    ri.type = icmp_header->icmp_type;

    icmp_header = (struct icmp *)((void *)icmp_header + 8 + ip_header_len);

    ri.id = icmp_header->icmp_hun.ih_idseq.icd_id;
    ri.seq = icmp_header->icmp_hun.ih_idseq.icd_seq;

    return ri;
}