/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** launch_utils.h
*/

#pragma once

#include "server/data_utils.h"

void clear_serverset(server_t server);

int setup_serverset(server_t server);

int server_select(server_t server, int max_fd);

server_t *init_server(server_t *server, unsigned short port);

int teams_server(int port);
