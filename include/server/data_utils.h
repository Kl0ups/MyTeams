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

typedef enum database_depth {
    NONE = -1,
    CLIENTS,
    DISCUSSIONS,
    TEAMS,
    CHANNELS,
    THREADS,
    MESSAGES
} db_depth_t;


typedef struct sockaddr_in socket_t;

typedef struct server_s {
    int fd;
    socket_t *info;
    fd_set *w_set;
    fd_set *r_set;

    client_t *clients;
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