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
#include <json-c/json.h>

#define MAX_LEN_RCV 8192

void receive_message(int socket, char *message)
{

    while (1)
    {
        int received = recv(socket, message, MAX_LEN_RCV - 1, 0); // receive msg

        if (received == -1)
        {
            perror("Error receiving");
            return;
        }
        else if (received > MAX_LEN_RCV - 1)
        { // if overflow max defined
            perror("Error word is too long");
            return;
        }
        else if (received >= 0)
        { // ok
            message[received] = '\0';
            return;
        }
    }
}

void send_message(int socket, char *message)
{

    if (strlen(message) > MAX_LEN_RCV - 1)
    {
        perror("String is too big");
        return;
    }

    while (1)
    {
        int sent = send(socket, message, strlen(message), 0);
        if (sent == -1)
        {
            perror("Error sending");
            return;
        }
        else if (sent >= 0)
        {
            return;
        }
    }
}

void create_profile(int socket)
{
    char buffer[512];
    char message[50];
    int year;

    // Get email
    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get name

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get last name

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get residence

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get academic formation

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get skills

    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get graduation year
    receive_message(socket, message);
    printf("%s", message);
    memset(message, 0, sizeof(message)); // reset to empty

    scanf(" %[^\n]", buffer);
    send_message(socket, buffer);

    // Get status
    printf("\n");
    receive_message(socket, buffer);
    printf("%s", buffer);

    return;
}

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
    printf("8: Exit\n");
    printf("\n");

    if (scanf("%d", &opt) == 1)
    {
        return opt;
    }
    else
    {
        return 8;
    }
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
