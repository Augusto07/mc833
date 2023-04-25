#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../model/profile.h"
#include "client_manager.c"

#define PORT "1969" // the port client will be connecting to 
#define MAXDATASIZE 100 // max number of bytes we can get at once 

int main(int argc, char *argv[]){
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    int option = 0;
    printf("\n");
    printf("Hello! Choose your option!\n");

    while (option != 8){
        option = get_option();
        int bytes_sent = send(sockfd, &option, sizeof(option), 0);
        char str[50];
        switch(option){
                    case 1:
                        printf("\n");
                        create_profile(sockfd);
                        printf("\n");
                    break;

                    case 2:
                        printf("Insert profile email:\n");
                        scanf(" %[^\n]", str);
                        general_function(sockfd, str);
                    break;

                    case 3:
                        printf("Insert profile email:\n");
                        scanf(" %[^\n]", str);
                        general_function(sockfd, str);
                    break;

                    case 4:
                        printf("Insert course:\n");
                        scanf(" %[^\n]", str);
                        general_function(sockfd, str);
                    break;

                    case 5:
                        printf("Insert skill:\n");
                        scanf(" %[^\n]", str);
                        general_function(sockfd, str);
                    break;

                    case 6:
                        printf("Insert graduation year:\n");
                        scanf(" %[^\n]", str);
                        general_function(sockfd, str);
                    break;

                    case 7:
                        general_function(sockfd, str);
                    break;
                    
                    case 8:
                    break;

                    default:
                        printf("\n Insert a valid option! \n");
                }
    }

    close(sockfd);

    return 0;
}