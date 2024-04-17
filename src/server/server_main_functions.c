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

#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

// static int handle_read_set(server_t *serv)
// {
//     int ret = 0;

//     if (FD_ISSET(serv->fd, serv->r_set)) {
//         add_client(serv);
//         return 0;
//     }
//     ret = handle_clients(serv);
//     if (ret == SYSTEM_ERROR && close(serv->fd)) {
//         return -1;
//     }
//     print_clients(serv, ret);
//     return 0;
// }

// static int handle_write_set(server_t *serv);

void server_free_data(server_t *serv)
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

// TODO: fix this function
// int max_fd = 0;
// int read = 0;
// int write = 0;

// while (1) {
//     clear_serverset(*serv);
//     max_fd = setup_serverset(*serv);
//     if (server_select(*serv, max_fd)) {
//         close(serv->fd);
//         return 84;
//     }
//     read = handle_read_set(serv);
//     write = handle_write_set(serv);
//     if (write < 0 || read < 0) {
//         return 84;
//     }
// }
static int server_loop(server_t *serv)
{
    printf("Server started\n");
    server_free_data(serv);
    return 0;
}

static server_t *start_server(server_t *inst, int port)
{
    int db = check_database();

    if (port < 0 || !inst) {
        return NULL;
    }
    *inst = init_server(port);
    if (!inst) {
        return NULL;
    }
    if (load_database(inst, db) == -1) {
        return NULL;
    }
    return inst;
}

int teams_server(int port)
{
    server_t *serv = malloc(sizeof(server_t));

    if (!start_server(serv, port)) {
        write(2, "Error while starting server\n", 29);
        return 84;
    }
    return server_loop(serv);
}
