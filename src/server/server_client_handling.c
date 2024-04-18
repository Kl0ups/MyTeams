/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_client_handling.c
*/
#include "server/data_utils.h"
#include "server/client_management.h"
#include "server/request_handlers.h"
#include <sys/socket.h>
#include <sys/select.h>

static void print_server_log(server_t *serv, int ret)
{
    (void)serv;
    (void)ret;
}

static int handle_clients_read(server_t *server)
{
    client_t *client = NULL;

    for (unsigned int i = 0; i < server->client_nb; i++) {
        client = &(server->clients[i].info);
        if (FD_ISSET(client->fd, server->r_set))
            return handle_request(server);
    }
    return SYSTEM_ERROR;
}

int manage_read_set(server_t *serv)
{
    if (FD_ISSET(serv->fd, serv->r_set)) {
        return add_temp_client(serv);
    }
    return (handle_clients_read(serv) == SYSTEM_ERROR ? -1 : 0);
}

static int handle_clients_write(server_t *serv)
{
    client_t *client = NULL;
    transfer_t *data = NULL;

    for (unsigned int i = 0; i < serv->client_nb; i++) {
        client = &(serv->clients[i].info);
        data = &(serv->clients[i].data);
        if (FD_ISSET(client->fd, serv->w_set)) {
            ssize_t byte = send(client->fd, data, sizeof(transfer_t), 0);
            return byte < 0 ? 1 : byte;
        }
    }
    return 0;
}

int manage_write_set(server_t *serv)
{
    int ret = 0;

    ret = handle_clients_write(serv);
    if (ret == SYSTEM_ERROR)
        return -1;
    print_server_log(serv, ret);
    return 0;
}
