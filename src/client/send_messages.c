/*
** EPITECH PROJECT, 2024
** send_messages
** File description:
** send_messages
*/

#include <fcntl.h>
#include "client/client.h"
#include "client/logging_client.h"
#include "common_utils.h"

const char *str_id(uuid_t id)
{
    static const char new_id[37] = {};

    uuid_parse(new_id, id);
    return new_id;
}

static int handle_display_command0(char *command, transfer_t dt)
{
    if (strcmp(command, "LOG IN")) {
        return client_event_logged_in(str_id(dt.p_data[0].client.id)
        , dt.p_data[0].client.username);
    }
    if (strcmp(command, "LOG OUT")) {
        return client_event_logged_out(str_id(dt.p_data[0].client.id)
        , dt.p_data[0].client.username);
    }
    if (strcmp(command, "MESSAGE RECEIVED")) {
        return client_event_private_message_received(
        str_id(dt.p_data[0].message.t_client), dt.p_data[0].message.msg);
    }
    if (strcmp(command, "THREAD REPLY RECEIVED")) {
        return client_event_thread_reply_received(str_id(dt.p_data[0].team.id)
        , str_id(dt.p_extra.message.r_client)
        , str_id(dt.p_extra.message.t_client), dt.p_extra.message.msg);
    }
    if (strcmp(command, "ALREADY EXISTS"))
        return client_error_already_exist();
    return handle_display_command1(command, dt);
}

static int clearfd(user_t *user)
{
    FD_ZERO(&user->read);
    FD_ZERO(&user->write);
    FD_SET(user->sockfd, &user->read);
    FD_SET(user->sockfd, &user->write);
    FD_SET(user->stdin_fd, &user->read);
    return 0;
}

static user_t get_commands(user_t user)
{
    int len;

    if (FD_ISSET(user.stdin_fd, &user.read)) {
        user.nb_buf++;
        user.buffers = realloc(user.buffers, user.nb_buf * sizeof(char *));
        user.buffers[user.nb_buf - 1] = malloc(user.size);
        getline(&user.buffers[user.nb_buf - 1], &user.size, stdin);
        len = strlen(user.buffers[user.nb_buf - 1]);
        user.buffers[user.nb_buf - 1][len - 1] = '\r';
        user.buffers[user.nb_buf - 1][len] = '\n';
    }
    if (FD_ISSET(user.sockfd, &user.write)) {
        if (user.nb_buf != 0) {
            send(user.sockfd, user.buffers[0], user.size + 1, 0);
            free(user.buffers[0]);
            user.buffers = &user.buffers[1];
            user.nb_buf--;
        }
    }
    return user;
}

int send_messages(user_t user)
{
    if (fcntl(user.stdin_fd, F_SETFL, O_NONBLOCK) < 0)
        return 1;
    while (1) {
        clearfd(&user);
        if (select(user.sockfd, &user.read, &user.write, NULL, NULL) < 0)
            return 1;
        if (FD_ISSET(user.sockfd, &user.read)) {
            recv(user.sockfd, &user.infos, sizeof(transfer_t), 0);
            handle_display_command0(user.infos.t_command, user.infos);
        }
        user = get_commands(user);
    }
    free(user.buffers);
}
