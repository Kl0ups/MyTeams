/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_client_loading.c
*/

#include "server/data_utils.h"
#include <sys/socket.h>
#include <stdlib.h>

static int init_client_infos(client_t *client)
{
    client->username = NULL;
    client->password = NULL;
    client->is_active = true;
    client->channel = NULL;
    client->team = NULL;
    client->thread = NULL;
    client->r_msg = NULL;
    client->t_msg = NULL;
    return 0;
}

int add_temp_client(server_t *server)
{
    int new_fd = 0;
    int new_size = server->client_nb + 1;
    socket_t *new_addr;
    socklen_t len = sizeof(socket_t *);

    new_fd = accept(server->fd, (struct sockaddr *)&new_addr, &len);
    if (new_fd < 0) {
        return 1;
    }
    server->clients = realloc(server->clients, sizeof(client_t) * new_size);
    if (!server->clients)
        return SYSTEM_ERROR;
    server->clients[new_size].info.fd = new_fd;
    server->client_nb += 1;
    return init_client_infos(&server->clients[new_size].info);
}
