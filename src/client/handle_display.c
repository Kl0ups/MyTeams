/*
** EPITECH PROJECT, 2024
** send_messages
** File description:
** send_messages
*/

#include "client/client.h"
#include "client/logging_client.h"
#include "common_utils.h"

static int handle_display_command5(char *command, transfer_t dt)
{
    if (strcmp(command, "THREAD CREATED")) {
        return client_print_thread_created(str_id(dt.p_data[0].thread.id)
        , str_id(dt.p_data[0].thread.owner), dt.p_data[0].thread.ctt
        , dt.p_data[0].thread.name, dt.p_data[0].thread.post);
    }
    if (strcmp(command, "REPLY CREATED")) {
        return client_print_reply_created(str_id(dt.p_data[0].message.id)
        , str_id(dt.p_data[0].message.t_client), dt.p_data[0].message.ctt
        , dt.p_data[0].message.msg);
    }
    if (strcmp(command, "SUBSCRIBED")) {
        return client_print_subscribed(str_id(dt.p_data[0].client.id)
        , str_id(dt.p_extra.team.id));
    }
    if (strcmp(command, "UNSUBSCRIBED")) {
        return client_print_unsubscribed(str_id(dt.p_data[0].client.id)
        , str_id(dt.p_extra.team.id));
    }
    return handle_display_command6(command, dt);
}

static int handle_display_command4(char *command, transfer_t dt)
{
    if (strcmp(command, "CHANNEL")) {
        return client_print_channel(str_id(dt.p_data[0].channel.id)
        , dt.p_data[0].channel.name, dt.p_data[0].channel.description);
    }
    if (strcmp(command, "TEAM CREATED")) {
        return client_print_team_created(str_id(dt.p_data[0].team.id)
        , dt.p_data[0].team.name, dt.p_data[0].team.description);
    }
    if (strcmp(command, "CHANNEL CREATED")) {
        return client_print_channel_created(str_id(dt.p_data[0].channel.id)
        , dt.p_data[0].channel.name, dt.p_data[0].channel.description);
    }
    if (strcmp(command, "CHANNELS")) {
        for (unsigned int i = 0; i < dt.p_size; i++) {
            client_team_print_channels(str_id(dt.p_data[i].channel.id)
            , dt.p_data[i].channel.name, dt.p_data[i].channel.description);
        }
        return 0;
    }
    return handle_display_command5(command, dt);
}

static int handle_display_command3(char *command, transfer_t dt)
{
    if (strcmp(command, "MESSAGES")) {
        for (unsigned int i = 0; i < dt.p_size; i++) {
            client_private_message_print_messages(
            str_id(dt.p_data[i].message.t_client)
            , dt.p_data[i].message.ctt, dt.p_data[i].message.msg);
        }
        return 0;
    }
    if (strcmp(command, "ERROR TEAM"))
        return client_error_unknown_team(str_id(dt.p_data[0].team.id));
    if (strcmp(command, "ERROR CHANNEL"))
        return client_error_unknown_channel(str_id(dt.p_data[0].channel.id));
    if (strcmp(command, "ERROR THREAD"))
        return client_error_unknown_thread(str_id(dt.p_data[0].thread.id));
    if (strcmp(command, "TEAM")) {
        return client_print_team(str_id(dt.p_data[0].team.id)
        , dt.p_data[0].team.name, dt.p_data[0].team.description);
    }
    return handle_display_command4(command, dt);
}

static int handle_display_command2(char *command, transfer_t dt)
{
    if (strcmp(command, "USERS")) {
        for (unsigned int i = 0; i < dt.p_size; i++) {
            client_print_users(str_id(dt.p_data[i].client.id)
            , dt.p_data[i].client.username, dt.p_data[i].client.is_active);
        }
        return 0;
    }
    if (strcmp(command, "TEAMS")){
        for (unsigned int i = 0; i < dt.p_size; i++) {
            client_print_teams(str_id(dt.p_data[i].team.id)
            , dt.p_data[i].team.name, dt.p_data[i].team.description);
        }
        return 0;
    }
    if (strcmp(command, "THREAD")) {
        return client_print_thread(str_id(dt.p_data[0].thread.id)
        , str_id(dt.p_data[0].thread.owner), dt.p_data[0].thread.ctt
        , dt.p_data[0].thread.name, dt.p_data[0].thread.post);
    }
    return handle_display_command3(command, dt);
}

int handle_display_command1(char *command, transfer_t dt)
{
    if (strcmp(command, "EVENT TEAM CREATED")) {
        return client_event_team_created(str_id(dt.p_data[0].team.id)
        , dt.p_data[0].team.name, dt.p_data[0].team.description);
    }
    if (strcmp(command, "EVENT CHANNEL CREATED")) {
        return client_event_channel_created(str_id(dt.p_data[0].channel.id)
        , dt.p_data[0].channel.name, dt.p_data[0].channel.description);
    }
    if (strcmp(command, "EVENT THREAD CREATED")) {
        return client_event_thread_created(str_id(dt.p_data[0].thread.id)
        , str_id(dt.p_data[0].thread.owner), dt.p_data[0].thread.ctt
        , dt.p_data[0].thread.name, dt.p_data[0].thread.post);
    }
    if (strcmp(command, "UNAUTHORIZED"))
        return client_error_unauthorized();
    if (strcmp(command, "USER")) {
        return client_print_user(str_id(dt.p_data[0].client.id)
        , dt.p_data[0].client.username, dt.p_data[0].client.is_active);
    }
    return handle_display_command2(command, dt);
}
