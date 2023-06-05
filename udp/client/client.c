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
#include "client.h"
#include "../model/profile.h"

#define PORT "8080" // Specify your desired port number
#define MAXDATASIZE 100
#define MAX_LEN_RCV 16384
#define MAXLINE 1024


void image_downloader(int sockfd, char *name)
{
    FILE *image_file;
    size_t bytes_received = 0;
    char buffer[MAXLINE];
    char filename[MAXLINE] = {0};

    image_file = fopen(filename, "w");
    if (image_file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ssize_t image_bytes_received = recvfrom(sockfd, buffer, MAXLINE, 0, NULL, NULL);
        if (image_bytes_received <= 0)
        {
            break;
        }

        printf("Received %ld bytes\n", image_bytes_received);

        size_t bytes_to_be_written = fwrite(buffer, sizeof(char), image_bytes_received, image_file);
        if (bytes_to_be_written != image_bytes_received)
        {
            perror("Error writing to file");
            exit(EXIT_FAILURE);
        }

        bytes_received += bytes_to_be_written;
    }

    fclose(image_file);
    printf("Successfully received %ld bytes\n", bytes_received);
}

void image_sender(int sockfd, struct sockaddr_in servaddr, socklen_t servlen, char *path)
{
    FILE *fp = fopen(path, "rb");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[MAXLINE];
    int bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        ssize_t bytesSent = sendto(sockfd, buffer, bytes_read, 0, (const struct sockaddr *)&servaddr, servlen);
        if (bytesSent < 0)
        {
            perror("Error sending file");
            exit(EXIT_FAILURE);
        }
        bzero(buffer, MAXLINE);
    }

    printf("Image sent successfully.\n");
    fclose(fp);
}

// check and recv msg
void receive_message(int socket, char *message) {
    while (1) {
        int received = recvfrom(socket, message, MAX_LEN_RCV - 1, 0, NULL, NULL);
        if (received == -1 || received > MAX_LEN_RCV - 1) {
            perror("Error receiving");
            return;
        }
        message[received] = '\0';
        return;
    }
}

void send_message(int socket, char *message) {
    if (strlen(message) > MAX_LEN_RCV - 1) {
        perror("String is too big");
        return;
    }

    while (1) {
        int sent = sendto(socket, message, strlen(message), 0, NULL, 0);
        if (sent == -1) {
            perror("Error sending");
            return;
        }
        return;
    }
}

// aux function to create a profile
void create_profile(int socket)
{
    char sendmsg[512];
    char message[64];
    int year;

    // Get email
    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get name

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get last name

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get residence

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get academic formation

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get skills

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get graduation year
    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", sendmsg);
    send_message(socket, sendmsg);

    // Get status
    printf("\n");
    receive_message(socket, sendmsg);
    printf("%s", sendmsg);

    return;
}

// generic function to send and receive msgs
void general_function(int socket, char *sendmsg)
{

    char response[MAX_LEN_RCV];
    send_message(socket, sendmsg);
    receive_message(socket, response);
    memset(sendmsg, 0, sizeof(sendmsg)); // reset to empty

    printf("\n");
    printf("===================================\n");
    printf("\n");
    printf("%s", response);
    printf("===================================\n");
    printf("\n");
    return;
}



// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}



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