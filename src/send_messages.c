/*
** EPITECH PROJECT, 2024
** send_messages
** File description:
** send_messages
*/

#include "client/client.h"

int send_messages(int sockfd)
{
    size_t size = 512;
    char *buffer = malloc(size);

    read(sockfd, buffer, size);
    write(0, buffer, size);
    bzero(buffer, size);
    while (1) {
        getline(&buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\r';
        buffer[strlen(buffer)] = '\n';
        write(sockfd, buffer, size + 1);
        bzero(buffer, size);
        read(sockfd, buffer, size);
        write(0, buffer, size);
        bzero(buffer, size);
    }
    return 0;
}
