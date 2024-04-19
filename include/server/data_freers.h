/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** data_freers.h
*/

#pragma once

#include "server/data_utils.h"

void server_clear_clients(server_t *serv);

void server_clear_teams(server_t *serv);

void server_clear_channels(server_t *serv);

void server_clear_threads(server_t *serv);

void server_clear_msgs(server_t *serv);
