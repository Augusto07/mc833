#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int socket_desc;
socket_desc = socket(AF_UNSPEC, SOCK_STREAM, 0); //domain = unspecified, type = TCP, protocol = match TCP
