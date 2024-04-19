/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** data_utils.h
*/

#pragma once

#include "common_utils.h"
#include <sys/types.h>

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define SYSTEM_ERROR 1
#define SYSTEM_OK 0

typedef enum rfc_status {
    HELP_OK = 110,
    HELP_ERROR = 111,
    LOGIN_OK = 210,
} rfc_status_t;

typedef struct cmd_tab_s {
    char *cmd;
    rfc_status_t (*func)(server_t *serv, unsigned int client_index, char **args);
    size_t max_args;
} cmd_tab_t;

typedef enum database_depth {
    NONE = -1,
    CLIENTS,
    DISCUSSIONS,
    TEAMS,
    CHANNELS,
    THREADS,
    MESSAGES
} db_depth_t;

typedef struct w_client_s {
    client_t info;
    transfer_t data;
} w_client_t;

typedef struct sockaddr_in socket_t;

typedef struct server_s {
    int fd;
    socket_t *info;
    fd_set *w_set;
    fd_set *r_set;

    w_client_t *clients;
    team_t *teams;
    channel_t *channels;
    thread_t *threads;
    message_t *messages;

    unsigned int client_nb;
    unsigned int team_nb;
    unsigned int channel_nb;
    unsigned int thread_nb;
    unsigned int message_nb;
} server_t;

typedef struct load_tab_s {
    db_depth_t type;
    int (*load)(server_t *serv);
} load_tab_t;
