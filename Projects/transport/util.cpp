#include "util.hpp"

using namespace std;

Dgram::Dgram()
{
    this->request = "";
    this->data = "";
}

Dgram::Dgram(std::string request, std::string data)
{
    this->request = request;
    this->data = data;
}

string Dgram::get_data(){
    return this->data;
}

string Dgram::get_request(){
    return this->request;
}

void Dgram::set_data(string data){
    this->data = data;
}

void Dgram::set_request(string req){
    this->request = req;
}

Udp::Udp(char *argv[])
{
    this->port = atoi(argv[2]);
    this->ip = argv[1];
    // open fstream file, trunc - when not exists create it
    file.open(argv[3], ios::in | ios::out | ios::trunc);

    this->bytes_requested = atoi(argv[4]);
    this->datagram_count = (this->bytes_requested + DATAGRAM_SIZE - 1) / DATAGRAM_SIZE;

    // initialize the sockaddr structure
    init_sockaddr();
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->sockfd < 0)
    {
        cerr << "Socket error, exiting \n";
        exit(EXIT_FAILURE);
    }
    this->received_dgrams = 0;
}

// initializing method for sockaddr struct
void Udp::init_sockaddr()
{
    bzero(&this->server_addr, sizeof(this->server_addr));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(this->port);
    inet_pton(AF_INET, this->ip.c_str(), &this->server_addr.sin_addr);
}

bool Udp::finished()
{
    return this->received_dgrams * DATAGRAM_SIZE >= this->bytes_requested;
}

void Udp::dgram_prepare(int data_size)
{
    int id = this->received_dgrams;
    // create request out of data_size
    string request = "GET " + to_string(id * DATAGRAM_SIZE) + " " + to_string(data_size) + "\n";
    this->dgram = Dgram(request, "");
}

// calculate size of dgram
int Udp::calculate_size()
{   
    //means we are in last dgram, send remainder
    if (this->datagram_count - 1 == this->received_dgrams){
        return this->bytes_requested - (DATAGRAM_SIZE * this->received_dgrams);
    }
    else{
        return DATAGRAM_SIZE;
    }
    /*
    int last_b = this->bytes_requested - (this->received_dgrams * DATAGRAM_SIZE);
    int data_size = DATAGRAM_SIZE < last_b ? DATAGRAM_SIZE : last_b;
    return data_size;
    */
}

void Udp::send_data()
{
    int data_size = calculate_size();
    dgram_prepare(data_size);

    string request = this->dgram.get_request();
    int req_size = request.size();

    //cout << "Sending datagram no." << this->received_dgrams  + 1 <<" req: " << request;

    if (sendto(this->sockfd,
               request.c_str(),
               req_size,
               0,
               (struct sockaddr *)&this->server_addr,
               sizeof(this->server_addr)) < 0)
    {
        cerr << "Send error\n";
        exit(EXIT_FAILURE);
    }
}

void Udp::init_select()
{
    FD_ZERO(&this->descriptors);
    FD_SET(this->sockfd, &this->descriptors);
    // wait max 1 sec
    this->tv.tv_sec = 0;
    this->tv.tv_usec = HALF_SECOND;
}

bool Udp::port_ip_correct(){
        char ip_rec[20];
        // get ip of sender
        inet_ntop(
            AF_INET,
            &(this->server_addr.sin_addr),
            ip_rec,
            sizeof(ip_rec)
        );

        int server_port = ntohs(this->server_addr.sin_port);

        if (ip_rec == this->ip && server_port == this->port){
            return true;
        }

        return false;
}

bool Udp::string_correct(char buffer[], int response_size){
    string dgram_data(buffer, (int)response_size);

    int start_data = dgram_data.find('\n') + 1;
    string req = dgram_data.substr(5, start_data - 6);
    string data = dgram_data.substr(start_data, (int)response_size);
    
    string wanted_req = this->dgram.get_request();
    int wanted = wanted_req.find('\n');


    wanted_req = wanted_req.substr(4, wanted - 4);
    // not the same, continue loop
    if (req.compare(wanted_req)){
        return false;
    }
    // strings same, set data in dgram
    this->dgram.set_data(data);
    return true;
}

void Udp::receive_data()
{
    // initialize select for further receiving

    bool received = false;

    while (!received)
    {
        init_select();

        int ready = select(this->sockfd + 1, &this->descriptors, NULL, NULL, &this->tv);

        if (ready == SELECT_ERROR)
        {
            cout << "Error when receiving data from fd, errno: " << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }
        else if (ready == SELECT_TIMEOUT)
        {
            #if DBG
            cout << "Packet lost" << endl;
            #endif
            send_data();
            continue;
        }

        else
        {
            // receive data to buffer
            char buffer[BUF_SIZE];
            socklen_t sender_len = sizeof(this->server_addr);
            ssize_t response_size = recvfrom(
                this->sockfd,
                buffer,
                BUF_SIZE,
                MSG_DONTWAIT,
                (struct sockaddr *)&this->server_addr,
                &sender_len);

            // check if ip and port is correct
            if (port_ip_correct()){
                if (string_correct(buffer, response_size)){
                    cout << "Received data no. " << this->received_dgrams + 1 << " out of: " << this->datagram_count << endl << endl;
                    received = true;
                }
                else{
                    send_data();
                    continue;
                }


            }

            else{
                cerr << "Port or ip not correct" << endl;
                send_data();
                continue;
            }


        }
    }

    this->received_dgrams += 1;
}

void Udp::write_data(){
    this->file << this->dgram.get_data();
    #if DBG
    msg(this->file.is_open());
    #endif
}

void Udp::file_close(){
    this->file.close();
}

Program::Program(char *argv[], int argc){
    this->argc = argc;
    this->udp_program = new Udp(argv);
}

void Program::check_input(int argc){
    if (argc != 5){
        cerr << "Wrong arguments!" << endl;
        exit(EXIT_FAILURE);
    }

    if (geteuid() != ROOT){
        cerr << "Cant execute without root thanks to virtual box :)" << endl;
        exit(EXIT_FAILURE);
    }    
}

void Program::run(){
    check_input(this->argc);

    while(!udp_program->finished()){
        udp_program->send_data();
        udp_program->receive_data();
        udp_program->write_data();
    }

    udp_program->file_close();

}

