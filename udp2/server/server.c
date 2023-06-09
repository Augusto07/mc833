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
#include "data_manager.c"

#define MYPORT "4950"    // the port users will be connecting to

#define MAXBUFLEN 17000

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("listener: bind");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to bind socket\n");
        return 2;
    }

    freeaddrinfo(servinfo);

    printf("listener: waiting to recvfrom...\n");

    while(1){

        char buf[MAXBUFLEN]; //buffer que guarda as msgs recebidas
        addr_len = sizeof their_addr; //tamanho end quem envia

        if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
            (struct sockaddr *)&their_addr, &addr_len)) == -1) {
            perror("recvfrom");
            exit(1); 
        } //recebe msg

        printf("listener: got packet from %s\n",
            inet_ntop(their_addr.ss_family,
                get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s)); //print de onde vem o pacote e preenche info

        buf[numbytes] = '\0';
        printf("listener: packet contains \"%s\"\n", buf); //printa o que foi recebido

        char opt = buf[strlen(buf) - 1] - '0';

        char *msg = strtok(buf, "&");

        printf("Mensagem: %s\n", msg);  
        printf("Dígito: %d\n", opt);  

        char *response;

        switch (opt)
            {
            case 1:;

                perfil profile; //cria struct profile
                fill_profile(&profile, msg); //preenche estrutura
                response = create_profile(&profile); //cria perfil no json

                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                break;

            case '2':

                response = delete_profile(msg);
                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                memset(msg, 0, sizeof(msg)); // reset to empty
                break;

            case '3':

                response = get_profile_info(msg);
                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                memset(msg, 0, sizeof(msg)); // reset to empty

                break;

            case '4':

                response = list_profiles_by_course(msg);
                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                memset(msg, 0, sizeof(msg)); // reset to empty
                break;

            case '5':

                response = list_profiles_by_skill(msg);
                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                memset(msg, 0, sizeof(msg)); // reset to empty
                break;

            case '6':

                response = list_profiles_by_year(msg);
                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                memset(msg, 0, sizeof(msg)); // reset to empty
                break;

            case '7':
                printf("Profile list:\n");

                printf("%s", msg);
                response = get_all_profiles();
                printf("%s", response);
                send_message(sockfd, response, (struct sockaddr *)&their_addr, addr_len);
                response = NULL;
                memset(msg, 0, sizeof(msg)); // reset to empty
                break;
            
            case '8':
                //caso download foto
                break;

            default:
                printf("Invalid option!\n");
            }
        //fazer a separação da opção após o &
        //implementar switch case para operações 
        //implementar mecanismo de resposta
        memset(buf, 0, sizeof(buf)); // reset to empty

    }
    close(sockfd);
    
    return 0;
}