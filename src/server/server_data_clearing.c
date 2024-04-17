/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_data_clearing.c
*/

#include "server/data_utils.h"
#include "server/data_freers.h"
#include <stdlib.h>
#include <unistd.h>

void server_clear_clients(server_t *serv)
{
    for (unsigned int i = 0; i < serv->client_nb; i++) {
        close(serv->clients[i].fd);
        if (serv->clients[i].username)
            free(serv->clients[i].username);
        if (serv->clients[i].password)
            free(serv->clients[i].password);
        if (serv->clients[i].t_msg)
            free(serv->clients[i].t_msg);
        if (serv->clients[i].r_msg)
            free(serv->clients[i].r_msg);
        if (serv->clients[i].team)
            free(serv->clients[i].team);
        if (serv->clients[i].channel)
            free(serv->clients[i].channel);
        if (serv->clients[i].thread)
            free(serv->clients[i].thread);
    }
    if (serv->clients)
        free(serv->clients);
}

void server_clear_teams(server_t *serv)
{
    for (unsigned int i = 0; i < serv->team_nb; i++) {
        if (serv->teams[i].name)
            free(serv->teams[i].name);
        if (serv->teams[i].description)
            free(serv->teams[i].description);
        if (serv->teams[i].channels)
            free(serv->teams[i].channels);
        if (serv->teams[i].members)
            free(serv->teams[i].members);
    }
    if (serv->teams)
        free(serv->teams);
}

void server_clear_channels(server_t *serv)
{
    for (unsigned int i = 0; i < serv->channel_nb; i++) {
        if (serv->channels[i].name)
            free(serv->channels[i].name);
        if (serv->channels[i].description)
            free(serv->channels[i].description);
        if (serv->channels[i].threads)
            free(serv->channels[i].threads);
        if (serv->channels[i].members)
            free(serv->channels[i].members);
    }
    if (serv->channels)
        free(serv->channels);
}

void server_clear_threads(server_t *serv)
{
    for (unsigned int i = 0; i < serv->thread_nb; i++) {
        if (serv->threads[i].name)
            free(serv->threads[i].name);
        if (serv->threads[i].post)
            free(serv->threads[i].post);
        if (serv->threads[i].r_message)
            free(serv->threads[i].r_message);
    }
    if (serv->threads)
        free(serv->threads);
}

void server_clear_msgs(server_t *serv)
{
    for (unsigned int i = 0; i < serv->message_nb; i++) {
        if (serv->messages[i].msg)
            free(serv->messages[i].msg);
    }
    if (serv->messages)
        free(serv->messages);
}
