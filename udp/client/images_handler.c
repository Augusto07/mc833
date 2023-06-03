#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>

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
