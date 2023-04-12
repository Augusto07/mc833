#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORTA "2000" //checked with sudo netstat -anpe | grep "<PORT_ADDR>"" | grep "LISTEN" cmd -> local port
#define BACKLOG 1

int main(){

    int status, client_socket, new_connection;
    struct addrinfo hints, *servinfo; 
    char * hostname;

    struct sockaddr_storage their_addr; //info from incoming connection
    socklen_t addr_size; //

    memset(&hints, 0, sizeof(hints)); // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP 
    hints.ai_flags = AI_PASSIVE;     // fill the IP of host machine

    if ((status = getaddrinfo("143.106.16.15", "1969", &hints, &servinfo)) != 0) { //get server info
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    client_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol); //create socket

    connect(client_socket, servinfo->ai_addr, servinfo->ai_addrlen); 

    if ((connect(client_socket, servinfo->ai_addr, servinfo->ai_addrlen)) != 0) { //get server info
        fprintf(stderr, "Unable to connect\n");
        exit(1);
    }
    //listen(server_socket, BACKLOG); //listen

    //addr_size = sizeof(their_addr);
    //new_connection = accept(server_socket, (struct sockaddr *)&their_addr, &addr_size);
    

    //struct sockaddr *other_hand_addr;
    //socklen_t addr_len;
    //addr_len = sizeof(struct sockaddr);
    //getpeername(new_connection, other_hand_addr, &addr_len);



    //close(server_socket);

    //send() and recv()


    //freeaddrinfo(servinfo); // free the linked-list

}
