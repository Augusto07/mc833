#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <json-c/json.h>
#include "../model/profile.h"
#include "server_manager.c"

#define PORT "1969"      // the port users will be connecting to
#define MAXDATASIZE 50    // max data received at one time by the user

int main(void)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t addr_len;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM; // Use UDP socket
    hints.ai_flags = AI_PASSIVE;    // Use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    printf("server: waiting for connections...\n");
    while (1)
    {
        addr_len = sizeof their_addr;
        char message[3];
        char *response;
        int numbytes;
        int opt;

        if ((numbytes = recvfrom(sockfd, &opt, MAXDATASIZE - 1, 0, (struct sockaddr *)&their_addr, &addr_len)) == -1)
        {
            perror("recvfrom");
            exit(1);
        }

        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);

        switch (opt)
        {
        case 1:
        {
            perfil profile;
            fill_profile(sockfd, &profile);
            response = create_profile(&profile);
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            break;
        }

        case 2:
            receive_message(sockfd, message);
            response = delete_profile(message);
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            memset(message, 0, sizeof(message)); // reset to empty
            break;

        case 3:
            receive_message(sockfd, message);
            response = get_profile_info(message);
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            memset(message, 0, sizeof(message)); // reset to empty
            break;

        case 4:
            receive_message(sockfd, message);
            response = list_profiles_by_course(message);
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            memset(message, 0, sizeof(message)); // reset to empty
            break;

        case 5:
            receive_message(sockfd, message);
            response = list_profiles_by_skill(message);
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            memset(message, 0, sizeof(message)); // reset to empty
            break;

        case 6:
            receive_message(sockfd, message);
            response = list_profiles_by_year(message);
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            memset(message, 0, sizeof(message)); // reset to empty
            break;

        case 7:
            printf("Profile list:\n");
            receive_message(sockfd, message);
            printf("%s", message);
            response = get_all_profiles();
            printf("%s", response);
            sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&their_addr, addr_len);
            response = NULL;
            memset(message, 0, sizeof(message)); // reset to empty
            break;

        case 8:
            printf("Client disconnected\n");
            break;

        default:
            printf("Invalid option!\n");
        }
    }

    close(sockfd);
    return 0;
}
