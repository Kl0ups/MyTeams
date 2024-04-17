/*
** EPITECH PROJECT, 2024
** send_messages
** File description:
** send_messages
*/

#include "client/client.h"
#include "client/logging_client.h"
#include "common_utils.h"

int handle_display_command1(char *command, transfer_t dt)
{
    if (strcmp(command, "EVENT TEAM CREATED")) {
        return client_event_team_created(dt.p_data[0].team.id
        , dt.p_data[0].team.name, dt.p_data[0].team.description);
    }
    if (strcmp(command, "EVENT CHANNEL CREATED")) {
        return client_event_channel_created(dt.p_data[0].channel.id
        , dt.p_data[0].channel.name, dt.p_data[0].channel.description);
    }
    if (strcmp(command, "EVENT THREAD CREATED")) {
        return client_event_thread_created(dt.p_data[0].thread.id
        , dt.p_extra.client.id, dt.p_data[0].thread.ctt
        , dt.p_data[0].thread.name, dt.p_data[0].thread.post);
    }
    if (strcmp(command, "UNAUTHORIZED"))
        return client_error_unauthorized();
    if (strcmp(command, "USER")) {
        return client_print_user(dt.p_data[0].client.id
        , dt.p_data[0].client.username, dt.p_data[0].client.is_active);
    }
    return handle_display_command2(command, dt);
}

int handle_display_command0(char *command, transfer_t dt)
{
    if (strcmp(command, "LOG IN")) {
        return client_event_logged_in(dt.p_data[0].client.id
        , dt.p_data[0].client.username);
    }
    if (strcmp(command, "LOG OUT")) {
        return client_event_logged_out(dt.p_data[0].client.id
        , dt.p_data[0].client.username);
    }
    if (strcmp(command, "MESSAGE RECEIVED")) {
        return client_event_private_message_received(
        dt.p_data[0].message.t_client, dt.p_data[0].message.msg);
    }
    if (strcmp(command, "THREAD REPLY RECEIVED")) {
        return client_event_thread_reply_received(dt.p_data[0].team.id
        , dt.p_extra.message.r_client, dt.p_extra.message.t_client
        , dt.p_extra.message.msg);
    }
    if (strcmp(command, "ALREADY EXISTS"))
        return client_error_already_exist();
    return handle_display_command1(command, dt);
}

int send_messages(int sockfd)
{
    size_t size = 512;
    char *buffer = malloc(size);
    transfer_t infos;

    while (1) {
        getline(&buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\r';
        buffer[strlen(buffer)] = '\n';
        write(sockfd, buffer, size + 1);
        bzero(buffer, size);
        read(sockfd, &infos, sizeof(transfer_t));
        handle_display_command1(infos.t_command, infos);
    }
    return 0;
}
