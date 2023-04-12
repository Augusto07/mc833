#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORTA "1969" //checked with sudo netstat -anpe | grep "<PORT_ADDR>"" | grep "LISTEN" cmd -> local port
#define BACKLOG 1

int main(){

    int status, server_socket, new_connection;
    struct addrinfo hints, *servinfo; 
    char * hostname;

    struct sockaddr_storage their_addr; //info from incoming connection
    socklen_t addr_size; //

    memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP 
    hints.ai_flags = AI_PASSIVE;     // fill the IP of host machine

    if ((status = getaddrinfo(NULL, PORTA, &hints, &servinfo)) != 0) { //get server (local) info
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    if ((server_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) == -1){ //create socket

        perror("server: socket");
        exit(1);
    }

    if (bind(server_socket, servinfo->ai_addr, servinfo->ai_addrlen) == -1){ //bind socket to port

        printf("Erro ao associar socket à porta local.");
        return 1;
    }

    freeaddrinfo(servinfo); // free the linked-list

    printf("server: waiting for connections...\n");


    while(1){

        if (listen(server_socket, BACKLOG) == 1){ //listen

            perror("listen");
            exit(1);
        } 
    }






    

    

    addr_size = sizeof(their_addr);
    new_connection = accept(server_socket, (struct sockaddr *)&their_addr, &addr_size);
    

    struct sockaddr *other_hand_addr;
    socklen_t addr_len;
    addr_len = sizeof(struct sockaddr);
    getpeername(new_connection, other_hand_addr, &addr_len);



    //close(server_socket);

    //send() and recv()


    

}







