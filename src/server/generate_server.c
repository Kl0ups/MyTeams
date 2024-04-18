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
    if (!server->r_set || !server->w_set)
        return 1;
    return 0;
}

static void init_server_socket(server_t *server, unsigned short port)
{
    server->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    server->info = create_socket_info(port);
}

server_t *init_server(server_t *serv, unsigned short port)
{
    int ok = 1;

    init_server_socket(serv, port);
    if (bind(serv->fd,
        (struct sockaddr *)serv->info, sizeof(socket_t)))
        return NULL;
    if (listen(serv->fd, 0))
        return NULL;
    if (setsockopt(serv->fd, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) < 0)
        return NULL;
    if (init_server_members(serv))
        return NULL;
    return serv;
}
