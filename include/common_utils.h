/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** common_utils.h
*/

#pragma once

#include <time.h>
#include <uuid/uuid.h>
#include <stdbool.h>

typedef struct client_s {
    uuid_t id;
    int fd;
    char *username, *password;
    char *t_msg, *r_msg;
    bool is_active;
    uuid_t *team, *channel, *thread;
} client_t;

typedef struct team_s {
    uuid_t id;
    time_t ctt;
    char *name, *description;
    uuid_t *channels;
    uuid_t *members;
} team_t;

typedef struct channel_s {
    uuid_t id;
    time_t ctt;
    char *name, *description;
    uuid_t *threads;
    uuid_t *members;
} channel_t;

typedef struct thread_s {
    uuid_t id;
    time_t ctt;
    char *name;
    char *post;
    uuid_t *r_message;
} thread_t;

typedef struct message_s {
    uuid_t id;
    time_t ctt;
    uuid_t t_client;
    uuid_t r_client;
    char *msg;
} message_t;

typedef union data_u {
    client_t client;
    team_t team;
    channel_t channel;
    thread_t thread;
    message_t message;
} data_t;

typedef struct transfer_s {
    char *t_command;
    unsigned int p_size;
    data_t *p_data;
    __attribute__((unused)) data_t p_extra;
} transfer_t;
