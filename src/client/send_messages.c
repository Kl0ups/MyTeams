/*
** EPITECH PROJECT, 2024
** send_messages
** File description:
** send_messages
*/

#include "client/client.h"
#include "client/logging_client.h"
#include "common_utils.h"

const char *str_id(uuid_t id)
{
    static const char new_id[37] = {};

    uuid_parse(new_id, id);
    return new_id;
}

static int handle_display_command1(char *command, transfer_t dt)
{
    if (strcmp(command, "750")) {
        return client_event_team_created(str_id(dt.p_data[0].team.id)
        , dt.p_data[0].team.name, dt.p_data[0].team.description);
    }
    if (strcmp(command, "760")) {
        return client_event_channel_created(str_id(dt.p_data[0].channel.id)
        , dt.p_data[0].channel.name, dt.p_data[0].channel.description);
    }
    if (strcmp(command, "770")) {
        return client_event_thread_created(str_id(dt.p_data[0].thread.id)
        , str_id(dt.p_data[0].thread.owner), dt.p_data[0].thread.ctt
        , dt.p_data[0].thread.name, dt.p_data[0].thread.post);
    }
    if (command[2] == '5')
        return client_error_unauthorized();
    if (strcmp(command, "320") || strcmp(command, "910")) {
        return client_print_user(str_id(dt.p_data[0].client.id)
        , dt.p_data[0].client.username, dt.p_data[0].client.is_active);
    }
    return handle_display_command2(command, dt);
}

static int handle_display_command0(char *command, transfer_t dt)
{
    if (strcmp(command, "210") || strcmp(command, "230")) {
        return client_event_logged_in(str_id(dt.p_data[0].client.id)
        , dt.p_data[0].client.username);
    }
    if (strcmp(command, "220") || strcmp(command, "240")) {
        return client_event_logged_out(str_id(dt.p_data[0].client.id)
        , dt.p_data[0].client.username);
    }
    if (strcmp(command, "430")) {
        return client_event_private_message_received(
        str_id(dt.p_data[0].message.t_client), dt.p_data[0].message.msg);
    }
    if (strcmp(command, "780")) {
        return client_event_thread_reply_received(str_id(dt.p_data[0].team.id)
        , str_id(dt.p_extra.message.r_client)
        , str_id(dt.p_extra.message.t_client), dt.p_extra.message.msg);
    }
    if (command[2] == '6')
        return client_error_already_exist();
    return handle_display_command1(command, dt);
}

int send_messages(int sockfd)
{
    size_t size = 524;
    char *buffer = malloc(size);
    transfer_t infos;

    while (1) {
        getline(&buffer, &size, stdin);
        buffer[strlen(buffer) - 1] = '\r';
        buffer[strlen(buffer)] = '\n';
        send(sockfd, buffer, size + 1, 0);
        bzero(buffer, size);
        recv(sockfd, &infos, sizeof(transfer_t), 0);
        handle_display_command0(infos.t_command, infos);
    }
    free(buffer);
    return 0;
}