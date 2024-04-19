/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_main_functions.c
*/

#include "server/data_utils.h"
#include "server/database_utils.h"
#include "server/launch_utils.h"
#include "server/data_freers.h"
#include "server/serverset_managers.h"
#include "server/logging_server.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

static void server_free_data(server_t *serv)
{
    if (serv->clients)
        server_clear_clients(serv);
    if (serv->teams)
        server_clear_teams(serv);
    if (serv->channels)
        server_clear_channels(serv);
    if (serv->threads)
        server_clear_threads(serv);
    if (serv->messages)
        server_clear_msgs(serv);
    if (serv->r_set)
        free(serv->r_set);
    if (serv->w_set)
        free(serv->w_set);
    if (serv->info)
        free(serv->info);
    free(serv);
}

static int server_loop(server_t *serv)
{
    int max_fd = 0;
    int read = 0;
    int write = 0;

    while (1) {
        clear_serverset(*serv);
        max_fd = setup_serverset(*serv);
        if (server_select(*serv, max_fd))
            return 1;
        read = manage_read_set(serv);
        write = manage_write_set(serv);
        if (write < 0 || read < 0)
            return 1;
    }
    return 0;
}

static server_t *start_server(server_t *inst, int port)
{
    int db = check_database();

    if (port < 0 || !inst)
        return NULL;
    if (!init_server(inst, port))
        return NULL;
    if (load_database(inst, db) == -1)
        return NULL;
    return inst;
}

int teams_server(int port)
{
    int ret = 0;
    server_t *serv = malloc(sizeof(server_t));

    if (!start_server(serv, port))
        return 84;
    ret = server_loop(serv);
    server_free_data(serv);
    return ret ? 84 : 0;
}
