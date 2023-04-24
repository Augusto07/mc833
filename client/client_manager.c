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

void receive_message(int socket, char* message){

    while(1){
        int received = recv(socket, message, 500, 0);
        if (received == -1) {
            perror("Error receiving email");
            return;
        }
        else if (received >= 0){
            message[strlen(message)] = '\0';
            return;
        }
    }
}

void send_message(int socket, char* message){

    while(1){
        int sent = send(socket, message, strlen(message), 0);
        if (sent == -1) {
            perror("Error sending");
            return;
        }
        else if (sent >= 0){
            return;
        }
    }
}

void create_profile(int socket) {
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
}
