/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server_data_management.c
*/

#include "common_utils.h"
#include <string.h>

client_t create_client(char *username, int fd)
{
    client_t new_client;

    if (strlen(username) > MAX_NAME_LENGTH)
        return (client_t){0};
    new_client.fd = fd;
    new_client.username = username;
    new_client.is_active = true;
    uuid_generate_random(new_client.id);
    new_client.channel = NULL;
    new_client.r_msg = NULL;
    new_client.t_msg = NULL;
    new_client.team = NULL;
    new_client.thread = NULL;
    return new_client;
}

team_t create_team(char *name, char *description)
{
    team_t new_team;

    if (strlen(name) > MAX_NAME_LENGTH
    || strlen(description) > MAX_DESCRIPTION_LENGTH)
        return (team_t){0};
    new_team.name = name;
    new_team.description = description;
    new_team.ctt = time(NULL);
    uuid_generate_random(new_team.id);
    new_team.members = NULL;
    return new_team;
}

channel_t create_channel(char *name, char *description)
{
    channel_t new_channel;

    if (strlen(name) > MAX_NAME_LENGTH
    || strlen(description) > MAX_DESCRIPTION_LENGTH)
        return (channel_t){0};
    new_channel.name = name;
    new_channel.description = description;
    new_channel.ctt = time(NULL);
    uuid_generate_random(new_channel.id);
    new_channel.members = NULL;
    new_channel.threads = NULL;
    return new_channel;
}

thread_t create_thread(char *title, char *message, uuid_t owner)
{
    thread_t new_thread;

    if (strlen(title) > MAX_NAME_LENGTH
    || strlen(message) > MAX_DESCRIPTION_LENGTH)
        return (thread_t){0};
    new_thread.name = title;
    new_thread.post = message;
    new_thread.ctt = time(NULL);
    uuid_generate_random(new_thread.id);
    uuid_copy(new_thread.owner, owner);
    new_thread.r_message = NULL;
    return new_thread;
}

message_t create_message(char *body, uuid_t recv, uuid_t send)
{
    message_t new_message;

    if (strlen(body) > MAX_BODY_LENGTH)
        return (message_t){0};
    new_message.msg = body;
    uuid_copy(new_message.r_client, recv);
    uuid_copy(new_message.t_client, send);
    new_message.ctt = time(NULL);
    uuid_generate_random(new_message.id);
    return new_message;
}
