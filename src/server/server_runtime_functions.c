/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_runtime_functions.h
*/

#include "server/data_utils.h"
#include <sys/select.h>
#include <stdio.h>

void clear_serverset(server_t server)
{
    w_client_t *client = server.clients;

    FD_ZERO(server.r_set);
    FD_ZERO(server.w_set);
    FD_SET(server.fd, server.w_set);
    FD_SET(server.fd, server.r_set);
    for (unsigned int i = 0; i < server.client_nb; i++) {
        FD_SET(client[i].info.fd, server.r_set);
        FD_SET(client[i].info.fd, server.w_set);
    }
}

int setup_serverset(server_t server)
{
    w_client_t *client = server.clients;
    int max_fd = server.fd;

    for (unsigned int i = 0; i < server.client_nb; i++) {
        FD_SET(client[i].info.fd, server.r_set);
        FD_SET(client[i].info.fd, server.w_set);
        max_fd = MAX(max_fd, client[i].info.fd);
    }
    return max_fd;
}

int server_select(server_t server, int max_fd)
{
    struct timeval timeout = {5, 0};
    int ret = select(max_fd + 1, server.r_set, server.w_set, NULL, &timeout);

    return ret < 0 ? 1 : 0;
}
