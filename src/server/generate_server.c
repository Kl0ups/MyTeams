/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** generate_server.c
*/
#include <stdlib.h>
#include <netinet/in.h>
#include <stdio.h>
#include "server/data_utils.h"

static socket_t *create_socket_info(unsigned short port)
{
    struct sockaddr_in *serv_info = malloc(sizeof(struct sockaddr_in));

    if (!serv_info) {
        perror("Failed to allocate memory for server info");
        return NULL;
    }
    serv_info->sin_family = AF_INET;
    serv_info->sin_port = htons(port);
    serv_info->sin_addr.s_addr = INADDR_ANY;
    return serv_info;
}

static int init_server_members(server_t *server)
{
    server->clients = NULL;
    server->client_nb = 0;
    server->channels = NULL;
    server->channel_nb = 0;
    server->messages = NULL;
    server->team_nb = 0;
    server->teams = NULL;
    server->thread_nb = 0;
    server->threads = NULL;
    server->message_nb = 0;
    server->messages = NULL;
    server->r_set = malloc(sizeof(fd_set));
    server->w_set = malloc(sizeof(fd_set));
    if (!server->r_set || !server->w_set) {
        perror("Failed to allocate memory for server fd_set");
        return 1;
    }
    return 0;
}

// TODO: fix setsockopt
server_t *init_server(server_t *server, unsigned short port)
{
    int enable = 1;

    server->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    server->info = create_socket_info(port);
    if (bind(server->fd,
        (struct sockaddr *)server->info, sizeof(socket_t))) {
        perror("Failed to bind server socket");
        return NULL;
    }
    if (listen(server->fd, 0)) {
        perror("Failed to listen on server socket");
        return NULL;
    }
    if (setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("Failed to set socket options");
        return NULL;
    }
    if (init_server_members(server)) {
        fprintf(stderr, "Failed to init server members\n");
        return NULL;
    }
    return server;
}
