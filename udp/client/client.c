#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <client_manager.c>

#define PORT "8080" // Specify your desired port number
#define MAXDATASIZE 100

int get_option()
{
    int option;
    printf("1. Create Profile\n");
    printf("2. Option 2\n");
    printf("3. Option 3\n");
    printf("4. Option 4\n");
    printf("5. Option 5\n");
    printf("6. Option 6\n");
    printf("7. Option 7\n");
    printf("8. Option 8\n");
    printf("9. Option 9\n");
    printf("10. Exit\n");
    printf("Enter your option: ");
    scanf("%d", &option);
    return option;
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2)
    {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM; // UDP socket

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to bind socket\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: sending to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    int option = 0;
    char str[MAXDATASIZE];

    printf("\nHello! Choose your option!\n");

    while (option != 10)
    {
        option = get_option();
        int bytes_sent = sendto(sockfd, &option, sizeof(option), 0, p->ai_addr, p->ai_addrlen);
        char str[MAXDATASIZE];
        switch (option)
        {
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
            printf("Profiles:\n");
            strcpy(str, "teste\n"); // just to consume the send opt
            general_function(sockfd, str);
            break;
        case 8:
            printf("Email to be linked to image profile:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str);
            break;
        case 9:
            printf("Email to get image profile:\n");
            scanf(" %[^\n]", str);
            general_function(sockfd, str);
            break;

        case 10:
            break;

        default:
            printf("\n Insert a valid option! \n");
        }
    }

    close(sockfd);
    return 0;
}