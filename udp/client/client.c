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
#include <netinet/ip.h>
#include <sys/time.h>

#define SERVERPORT "4950" // the port users will be connecting to
#define MAXDATASIZE 1000000
#define MAX_LEN_RCV 16384
#define MAXLINE 1024
#include "../model/profile.h"
#include <sys/poll.h>

#define TIMEOUT_MS 2000

// check and recv msg
void receive_message(int socket, char *message)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    addr_len = sizeof(struct sockaddr_storage);

    struct pollfd fds[1];
    fds[0].fd = socket;
    fds[0].events = POLLIN;

    int poll_status = poll(fds, 1, TIMEOUT_MS);
    if (poll_status == -1)
    {
        perror("Error in poll");
        return;
    }
    else if (poll_status == 0)
    {
        printf("Timeout occurred in receiving message\n");
        return;
    }

    if (fds[0].revents & POLLIN)
    {
        int received = recvfrom(socket, message, MAX_LEN_RCV - 1, 0,
                                (struct sockaddr *)&their_addr, &addr_len); // receive msg

        if (received == -1) // error recv
        {
            perror("Error receiving");
            return;
        }
        else if (received > MAX_LEN_RCV - 1) // overflow
        {
            perror("Error word is too long");
            return;
        }
        else if (received >= 0) // ok
        {
            message[received] = '\0';
            return;
        }
    }
}

// check and send msg
void send_message(int socket, char *message, struct addrinfo *p)
{
    struct pollfd fds[1];
    fds[0].fd = socket;
    fds[0].events = POLLOUT;

    int poll_status = poll(fds, 1, TIMEOUT_MS);
    if (poll_status == -1)
    {
        perror("Error in poll");
        return;
    }
    else if (poll_status == 0)
    {
        printf("Timeout occurred inside send message\n");
        return;
    }

    if (fds[0].revents & POLLOUT)
    {
        int sent = sendto(socket, message, strlen(message), 0, p->ai_addr, p->ai_addrlen);
        if (sent == -1) // error send
        {
            perror("Error sending");
            return;
        }
        else if (sent >= 0) // ok
        {
            return;
        }
    }
}
// aux function to create a profile
void create_profile(int socket, struct addrinfo *p)
{
    char sendmsg[MAX_LEN_RCV] = "";
    char message[64];

    // Get email

    printf("Insert email: \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "/");

    // Get name

    printf("Insert name: \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "/");

    // Get last name

    printf("Insert last name: \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "/");

    // Get residence

    printf("Insert residence: \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "/");

    // Get academic formation

    printf("Insert academic formation: \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "/");

    // Get skills

    printf("Insert skills separated by comma (skill1,skill2...): \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "/");

    // Get graduation year

    printf("Insert graduation year: \n");
    memset(message, 0, sizeof(message)); // reset to empty
    scanf(" %[^\n]", message);
    strcat(sendmsg, message);

    strcat(sendmsg, "&1");

    // Get status
    printf("\n");
    send_message(socket, sendmsg, p);
    char msg[200];
    receive_message(socket, msg);
    printf("%s", msg);

    return;
}

// generic function to send and receive msgs
void general_function(int socket, char *sendmsg, struct addrinfo *p, int msgcode)
{
    char code[5];

    sprintf(code, "&%d", msgcode);
    strcat(sendmsg, code); // concat sendmsg and &msgcode

    char response[MAX_LEN_RCV];

    send_message(socket, sendmsg, p);  // send message sendmsg
    receive_message(socket, response); // receive response response

    memset(sendmsg, 0, sizeof(sendmsg)); // reset to empty //reset msg to empty

    printf("\n");
    printf("===================================\n");
    printf("\n");
    printf("%s", response);
    printf("===================================\n");
    printf("\n");
    return;
}

void download_image(int socket, char *sendmsg, struct addrinfo *p, int msgcode)
{
    char code[5];

    char filename[100] = "";
    char *path = "images/";

    strcat(filename, path);
    strcat(filename, sendmsg);
    strcat(filename, ".jpg");

    sprintf(code, "&%d", msgcode);
    strcat(sendmsg, code); // concatenate sendmsg and &msgcode

    char response[MAX_LEN_RCV];

    send_message(socket, sendmsg, p); // send message sendmsg

    receive_message(socket, response);

    if (strcmp(response, "File does not exist") == 0)
    {
        printf("%s\n", response);
        return;
    }

    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Error creating the file\n");
        return;
    }

    struct pollfd fds[1];
    fds[0].fd = socket;
    fds[0].events = POLLIN;

    char buffer[2048];
    size_t total_bytes_received = 0;

    while (1)
    {
        int poll_status = poll(fds, 1, TIMEOUT_MS);
        if (poll_status == -1)
        {
            perror("Error in poll");
            break;
        }
        else if (poll_status == 0)
        {
            printf("Timeout occurred in downloading the image\n");
            break;
        }

        if (fds[0].revents & POLLIN)
        {
            ssize_t bytes_received = recv(socket, buffer, sizeof(buffer), 0);

            if (bytes_received <= 0)
            {
                if (bytes_received == 0)
                    break;
                printf("Error receiving!\n");
                break;
            }

            printf("Received %ld bytes\n", bytes_received);

            // Save the received data to the file
            size_t wbytes = fwrite(buffer, 1, sizeof(buffer), file);

            // // Verify if all the data was written correctly
            // if (bytes_received != wbytes)
            // {
            //     printf("Error writing!\n");
            //     break;
            // }

            // Update the total bytes received
            total_bytes_received += bytes_received;
        }
    }

    fclose(file);
    printf("Total bytes received: %zu\n", total_bytes_received);
}
// funct to take input opt from user
int get_option()
{
    int opt;
    printf("\n");
    printf("1: Create profile \n");
    printf("2: Delete profile \n");
    printf("3: Search profile by email \n");
    printf("4: Search profile(s) by course \n");
    printf("5: Search profile(s) by skill \n");
    printf("6: Search profile(s) by graduation year \n");
    printf("7: List all profiles\n");
    printf("8: Download image\n");
    printf("9: Exit\n");
    printf("\n");

    if (scanf("%d", &opt) == 1)
    {
        return opt;
    }
    else
    {
        return 9;
    }
}

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