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
#include "data_manager.c"

#define PORT "1969" // the port users will be connecting to
#define BACKLOG 1   // how many pending connections queue will hold
#define MAXDATASIZE 1000

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

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

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    printf("server: waiting for connections...\n");
    while (1)
    {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork())
        {                  // this is the child process
            close(sockfd); // child doesn't need the listener
            char message[MAXDATASIZE];
            char *response;
            int numbytes;
            int opt;

            while ((numbytes = recv(new_fd, &opt, MAXDATASIZE - 1, 0)) > 0)
            {

                printf("Received message: %d\n", opt);
                switch (opt)
                {
                case 1:;
                    perfil profile;
                    fill_profile(new_fd, &profile);
                    response = create_profile(&profile);
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    break;

                case 2:
                    receive_message(new_fd, message);
                    response = delete_profile(message);
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    memset(message, 0, sizeof(message)); // reset to empty
                    break;

                case 3:
                    receive_message(new_fd, message);
                    response = get_profile_info(message);
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    memset(message, 0, sizeof(message)); // reset to empty

                    break;

                case 4:
                    receive_message(new_fd, message);
                    response = list_profiles_by_course(message);
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    memset(message, 0, sizeof(message)); // reset to empty
                    break;

                case 5:
                    receive_message(new_fd, message);
                    response = list_profiles_by_skill(message);
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    memset(message, 0, sizeof(message)); // reset to empty
                    break;

                case 6:
                    receive_message(new_fd, message);
                    response = list_profiles_by_year(message);
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    memset(message, 0, sizeof(message)); // reset to empty
                    break;

                case 7:
                    printf("Profile list:\n");
                    receive_message(new_fd, message);
                    printf("%s", message);
                    response = get_all_profiles();
                    printf("%s", response);
                    send_message(new_fd, response);
                    response = NULL;
                    memset(message, 0, sizeof(message)); // reset to empty
                    break;

                default:
                    printf("Invalid option!\n");
                }
            }
            if (numbytes == -1)
            {
                perror("recv");
                exit(1);
            }
            close(new_fd); // parent doesn't need this
            exit(0);
        }
    }
    return 0;
}