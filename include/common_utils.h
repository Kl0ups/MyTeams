/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** common_utils.h
*/

#pragma once

#include <uuid/uuid.h>

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
    char *name, *description;
    uuid_t *channels;
    uuid_t *members;
} team_t;

typedef struct channel_s {
    uuid_t id;
    char *name, *description;
    uuid_t *threads;
    uuid_t *members;
} channel_t;

typedef struct thread_s {
    uuid_t id;
    char *name;
    char *post;
    uuid_t *r_message;
} thread_t;

typedef struct discussion_s {
    uuid_t id;
    uuid_t t_client;
    uuid_t r_client;
    char *msg;
} discussion_t;

typedef union data_u {
    client_t client;
    team_t team;
    channel_t channel;
    thread_t thread;
    discussion_t discussion;
} data_t;
