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
#include <netinet/ip.h>
#include <sys/time.h>

#define SERVERPORT "4950" // the port users will be connecting to
#define MAXDATASIZE 100
#define MAX_LEN_RCV 16384
#define MAXLINE 1024
#define TIMEOUT_MS 5000 // 5 seconds

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    if (argc != 2)
    {
        fprintf(stderr, "usage: talker hostname message\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to use IPv4
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1)
        {
            perror("talker: socket");
            continue;
        }

        break;
    }

    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_MS / 1000;           // seconds
    timeout.tv_usec = (TIMEOUT_MS % 1000) * 1000; // microseconds

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1)
    {
        perror("talker: setsockopt");
        return 3;
    }

    if (p == NULL)
    {
        fprintf(stderr, "talker: failed to create socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    int option = 0;
    char str[MAXDATASIZE];

    printf("\nHello! Choose your option!\n");

    while (option != 9)
    {
        option = get_option(); // option chosen by the user
        char str[MAXDATASIZE]; // string with info to be send

        switch (option)
        {
        case 1: // create profile
            printf("\n");
            create_profile(sockfd, p);
            printf("\n");
            break;

        case 2:
            printf("Insert profile email:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p, option);
            break;

        case 3:
            printf("Insert profile email:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p, option);
            break;

        case 4: // search profile by course
            printf("Insert course:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p, option);
            break;

        case 5: // search profile by skill
            printf("Insert skill:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p, option);
            break;

        case 6: // search profile by grad year
            printf("Insert graduation year:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str, p, option);
            break;

        case 7: // get all profiles
            printf("Profiles:\n");
            strcpy(str, "all"); // just to consume the send opt
            general_function(sockfd, str, p, option);
            break;

        case 8: // download image
            printf("Insert profile email:\n");
            scanf(" %[^\n]", str);
            download_image(sockfd, str, p, option);
            break;

        case 9: // exit
            break;

        default:
            printf("\n Insert a valid option! \n");
        }
    }

    close(sockfd);
    return 0;
}