#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "client_manager.c"

#define SERVERPORT "4950"    // the port users will be connecting to
#define MAXDATASIZE 100
#define MAX_LEN_RCV 16384
#define MAXLINE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    if (argc != 2) {
        fprintf(stderr,"usage: talker hostname message\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to use IPv4
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    int option = 0;
    char str[MAXDATASIZE];

    printf("\nHello! Choose your option!\n");

    while (option != 10)
    {
        option = get_option();
        printf("%d", option);
        int bytes_sent = sendto(sockfd, &option, sizeof(option), 0, p->ai_addr, p->ai_addrlen);
        printf("%d", bytes_sent);
        char str[MAXDATASIZE];
        switch (option)
        {
        case 1:
            printf("\n");
            create_profile(sockfd, p);
            printf("\n");
            break;

        case 2:
            printf("Insert profile email:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p);
            break;

        case 3:
            printf("Insert profile email:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p);
            break;

        case 4:
            printf("Insert course:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p);
            break;

        case 5:
            printf("Insert skill:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p);
            break;

        case 6:
            printf("Insert graduation year:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p);
            break;

        case 7:
            printf("Profiles:\n");
            strcpy(str, "teste\n"); // just to consume the send opt
            general_function(sockfd, str, p);
            break;
        case 8:
            printf("Insert profile email:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p);
            break;
        case 9:
            break;

        default:
            printf("\n Insert a valid option! \n");
        }
    }

    close(sockfd);
    return 0;
}