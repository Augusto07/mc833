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
#include "../model/profile.h"

#define MAX_LEN_RCV 16384

// check and recv msg
void receive_message(int socket, char *message)
{
    struct sockaddr_storage their_addr;
    socklen_t addr_len;

    while (1)
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

    if (strlen(message) > MAX_LEN_RCV - 1) // overflow
    {
        perror("String is too big");
        return;
    }

    while (1)
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
    printf("%s", sendmsg);

    return;
}

// generic function to send and receive msgs
void general_function(int socket, char *sendmsg, struct addrinfo *p, int msgcode)
{
    char code[5];

    sprintf(code, "&%d", msgcode);
    strcat(sendmsg, code); //concat sendmsg and &msgcode

    printf("%s\n", sendmsg);

    char response[MAX_LEN_RCV];

    send_message(socket, sendmsg, p); //send message sendmsg
    receive_message(socket, response); //receive response response

    memset(sendmsg, 0, sizeof(sendmsg)); // reset to empty //reset msg to empty

    printf("\n");
    printf("===================================\n");
    printf("\n");
    printf("%s", response);
    printf("===================================\n");
    printf("\n");
    return;
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