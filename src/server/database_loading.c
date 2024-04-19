/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** database_loading.c
*/

#include "server/data_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int load_clients(server_t *serv)
{
    FILE *file = fopen("database/clients", "r");

    while (feof(file)) {
        fread(&(serv->client_nb), sizeof(int), 1, file);
        serv->clients = calloc(serv->client_nb + 1, sizeof(w_client_t));
        if (!serv->clients)
            return SYSTEM_ERROR;
        for (unsigned int i = 0; i < serv->client_nb + 1; i++) {
            fread(&(serv->clients[i]), sizeof(w_client_t), 1, file);
        }
    }
    return SYSTEM_OK;
}

int load_teams(server_t *serv)
{
    FILE *file = fopen("database/teams", "r");

    while (feof(file)) {
        fread(&(serv->team_nb), sizeof(int), 1, file);
        serv->teams = calloc(serv->team_nb + 1, sizeof(team_t));
        if (!serv->teams)
            return SYSTEM_ERROR;
        for (unsigned int i = 0; i < serv->team_nb + 1; i++) {
            fread(&(serv->teams[i]), sizeof(team_t), 1, file);
        }
    }
    return SYSTEM_OK;
}

int load_channels(server_t *serv)
{
    FILE *file = fopen("database/channels", "r");

    while (feof(file)) {
        fread(&(serv->channel_nb), sizeof(int), 1, file);
        serv->channels = calloc(serv->channel_nb + 1, sizeof(channel_t));
        if (!serv->channels)
            return SYSTEM_ERROR;
        for (unsigned int i = 0; i < serv->channel_nb + 1; i++) {
            fread(&(serv->channels[i]), sizeof(channel_t), 1, file);
        }
    }
    return SYSTEM_OK;
}

int load_threads(server_t *serv)
{
    FILE *file = fopen("database/threads", "r");

    while (feof(file)) {
        fread(&(serv->thread_nb), sizeof(int), 1, file);
        serv->threads = calloc(serv->thread_nb + 1, sizeof(thread_t));
        if (!serv->threads)
            return SYSTEM_ERROR;
        for (unsigned int i = 0; i < serv->thread_nb + 1; i++) {
            fread(&(serv->threads[i]), sizeof(thread_t), 1, file);
        }
    }
    return SYSTEM_OK;
}

int load_messages(server_t *serv)
{
    FILE *file = fopen("database/messages", "r");

    while (feof(file)) {
        fread(&(serv->message_nb), sizeof(int), 1, file);
        serv->messages = calloc(serv->message_nb + 1,
            sizeof(message_t));
        if (!serv->messages)
            return SYSTEM_ERROR;
        for (unsigned int i = 0; i < serv->message_nb + 1; i++) {
            fread(&(serv->messages[i]), sizeof(message_t), 1, file);
        }
    }
    return SYSTEM_OK;
}
