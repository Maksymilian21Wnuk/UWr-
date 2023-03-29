// bez tego błąd w structach....
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>

// response codes of router
#define NO_RESPONSE 41
#define ACQUIRED_RESPONSE 42
#define NOT_EVERY_RESPONDED 43

extern struct icmp header;
extern struct sockaddr_in recipient;
extern struct timeval tv;
extern fd_set descriptors;

// very important info of
// receiver, type
// and variables id seq
// needed for matching correct process
typedef struct receiver_info
{
    int id;
    int seq;
    int type;
    
    int sender_id;
    int sender_seq;
} rec_info;

u_int16_t compute_icmp_checksum(const void *buff, int length);

void header_init(int);
void recipient_init(char *);
void select_util(int);
bool was_last(int, int);
void send_packet(int sockfd, struct icmp header, struct sockaddr_in recipient);
rec_info get_rec_info(u_int8_t *buffer);
