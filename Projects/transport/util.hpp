#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <errno.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

#define DATAGRAM_SIZE 1000
#define SELECT_TIMEOUT 0
#define SELECT_ERROR -1
#define BUF_SIZE 2048
#define ROOT 0
#define DBG 0
#define HALF_SECOND 5 * 10000

#define msg(x) cout << x << endl;
#define asdf cout << "ASDF" << endl;

class Dgram{
    private:
        // time from sending to receiving
        std::string request;
        std::string data;
    public:
        Dgram();
        Dgram(std::string request, std::string data);

        std::string get_request();
        void set_request(std::string req);
        std::string get_data();
        void set_data(std::string data);
};


class Udp{
    private:
        int port;
        std::string ip;
        // file output
        std::ofstream file;
        // bytes of file that are requested,
        // datagram count is number which
        // indicates datagrams needed to be sent
        int bytes_requested;
        int datagram_count;
        
        struct sockaddr_in server_addr;
	    int sockfd;

        // number of sent dgrams and received
        int received_dgrams;

        fd_set descriptors;
        struct timeval tv;

        Dgram dgram;

    private:
        // sockaddr and select initialization
        void init_sockaddr();
        void init_select();
        // calculate size of dgram
        int calculate_size();
        // check if ip correct
        bool port_ip_correct();
        // check if dgram string is same as requested
        bool string_correct(char buffer[], int rsize);
        // prepare dgram before sending
        void dgram_prepare(int data_size);
    
    public:
        Udp(char *argv[]);
        // returns whether job is finished
        bool finished();
        // method for sending data to server and receiving
        void send_data();
        void receive_data();
        // write to file data
        void write_data();
        // close fstream file
        void file_close();

};


class Program{
    private:
        Udp *udp_program;
        int argc;
        void check_input(int argc);
    public:
        Program(char *argv[], int argc);
        void run();
        
};
