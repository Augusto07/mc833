#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORTA "1969" //checked with sudo netstat -anpe | grep "<PORT_ADDR>"" | grep "LISTEN" cmd

int main(){

    int status, server_socket;
    struct addrinfo hints, *servinfo; 

    memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP 
    hints.ai_flags = AI_PASSIVE;     // fill the IP of host machine

    if ((status = getaddrinfo(NULL, PORTA, &hints, &servinfo)) != 0) { //get server info
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
    }

    server_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol); //create socket

    if (bind(server_socket, servinfo->ai_addr, servinfo->ai_addrlen) == 1){ //bind socket to port

        printf("Erro ao associar socket à porta local.");
        return 1;
    }


    //listen()

    //accept()

    //send() and recv()


    freeaddrinfo(servinfo); // free the linked-list


}







