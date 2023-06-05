#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT "8080" // Specify your desired port number
#define MAXDATASIZE 100
#define MAX_LEN_RCV 16384
#define MAXLINE 1024

void image_downloader(int sockfd, char *name);
void image_sender(int sockfd, struct sockaddr_in servaddr, socklen_t servlen, char *path);
void receive_message(int socket, char *message);
void send_message(int socket, char *message);
void create_profile(int socket);
void general_function(int socket, char *sendmsg);
void *get_in_addr(struct sockaddr *sa);
int get_option();

#endif
