/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** client_commands.h
*/

#pragma once

rfc_status_t command_login(
    server_t *server, unsigned int client_index, char **args);

char **get_cmd_args(const char *cmd_buffer);