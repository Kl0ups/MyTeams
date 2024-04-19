/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** database_utils.h
*/

#pragma once

#include "server/data_utils.h"

int load_clients(server_t *serv);

int load_teams(server_t *serv);

int load_channels(server_t *serv);

int load_threads(server_t *serv);

int load_messages(server_t *serv);

db_depth_t check_database(void);

int load_database(server_t *serv, db_depth_t db_depth);
