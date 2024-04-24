/*
** EPITECH PROJECT, 2024
** client
** File description:
** client
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <strings.h>
#include <string.h>
#include "common_utils.h"

typedef struct user_s {
    fd_set read;
    fd_set write;
    int sockfd;
    int stdin_fd;
    char **buffers;
    int nb_buf;
    size_t size;
    transfer_t infos;
} user_t;

int send_messages(user_t);
const char *str_id(uuid_t id);
int handle_display_command1(char *, transfer_t);
int handle_display_command6(char *, transfer_t);
