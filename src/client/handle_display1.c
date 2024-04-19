/*
** EPITECH PROJECT, 2024
** handle_client
** File description:
** handle_display
*/

#include "client/client.h"
#include "client/logging_client.h"
#include "common_utils.h"

int handle_display_command6(char *command, transfer_t dt)
{
    if (strcmp(command, "ERROR USER"))
        return client_error_unknown_user(str_id(dt.p_data[0].client.id));
    if (strcmp(command, "THREADS")) {
        for (unsigned int i = 0; i < dt.p_size; i++) {
            client_channel_print_threads(str_id(dt.p_data[i].thread.id)
            , str_id(dt.p_data[i].thread.owner), dt.p_data[i].thread.ctt
            , dt.p_data[i].thread.name, dt.p_data[i].thread.post);
        }
        return 0;
    }
    if (strcmp(command, "REPLIES")) {
        for (unsigned int i = 0; i < dt.p_size; i++) {
            client_thread_print_replies(str_id(dt.p_extra.thread.id)
            , str_id(dt.p_data[i].message.t_client), dt.p_data[i].message.ctt
            , dt.p_data[i].message.msg);
        }
        return 0;
    }
    write(0, "Unkown command\n", 15);
    return 1;
}
