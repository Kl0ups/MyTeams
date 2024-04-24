/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_request_handling.c
*/
#include "server/data_utils.h"
#include "server/client_commands.h"
#include <sys/socket.h>

static const cmd_tab_t cmd_tab[] = {
    {"/login", &command_login, 1},
    {"/logout", NULL, 0},
    {"/users", NULL, 0},
    {"/user", NULL, 1},
    {"/send", NULL, 2},
    {"/messages", NULL, 1},
    {"/subscribe", NULL, 1},
    {"/subscribed", NULL, 0},
    {"/unsubscribe", NULL, 1},
    {"/use", NULL, 1},
    {"/create", NULL, 2},
    {NULL, NULL, 0}
};

int handle_request(server_t *server, unsigned int client_index)
{
    client_t *client = &(server->clients[client_index].info);
    transfer_t *data = &(server->clients[client_index].data);
    char **args = NULL;
    ssize_t bytes = 0;

    bytes = recv(client->fd, client->r_msg, MAX_CLIENT_REQUEST_SIZE, 0);
    if (bytes == -1)
        return SYSTEM_ERROR;
    args = get_cmd_args(client->r_msg);
    for (size_t i = 0; cmd_tab[i].cmd != NULL; i++) {
        if (strcmp(args[0], cmd_tab[i].cmd) == 0) {
            return cmd_tab[i].func(server, client_index, args);
        }
    }
    return SYSTEM_ERROR;
}
