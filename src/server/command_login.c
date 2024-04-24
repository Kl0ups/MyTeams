/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** command_login.h
*/

#include "server/data_utils.h"

rfc_status_t command_login(server_t *server, unsigned int client_index, char **args)
{
    (void)server;
    (void)client_index;
    (void)args;
    return LOGIN_OK;
}
