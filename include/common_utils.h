/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** common_utils.h
*/

#pragma once

#include <time.h>
#include <uuid/uuid.h>
#include <stdbool.h>

/// @brief Structure containing all the data of a client
/// @param id The unique identifier of the client
/// @param fd The file descriptor of the client
/// @param username The username of the client
/// @param password The password of the client
/// @param t_msg The temporary sending message of the client
/// @param r_msg The temporary received message of the client
/// @param is_active The activity status of the client
/// @param team The selected team of the client (NULL if none selected)
/// @param channel The selected channel of the client (NULL if none selected)
/// @param thread The selected thread of the client (NULL if none selected)
typedef struct client_s {
    uuid_t id;
    int fd;
    char *username, *password;
    char *t_msg, *r_msg;
    bool is_active;
    uuid_t *team, *channel, *thread;
} client_t;

/// @brief Structure containing all the data of a team
/// @param id The unique identifier of the team
/// @param ctt The creation time of the team
/// @param name The name of the team
/// @param description The description of the team
/// @param channels The list of channels id of the team
/// @param members The list of members id of the team
typedef struct team_s {
    uuid_t id;
    time_t ctt;
    char *name, *description;
    uuid_t *channels;
    uuid_t *members;
} team_t;

/// @brief Structure containing all the data of a channel
/// @param id The unique identifier of the channel
/// @param ctt The creation time of the channel
/// @param name The name of the channel
/// @param description The description of the channel
/// @param threads The list of threads id of the channel
/// @param members The list of members id of the channel
typedef struct channel_s {
    uuid_t id;
    time_t ctt;
    char *name, *description;
    uuid_t *threads;
    uuid_t *members;
} channel_t;

/// @brief Structure containing all the data of a thread
/// @param id The unique identifier of the thread
/// @param ctt The creation time of the thread
/// @param owner The owner of the thread (client_t)
/// @param name The title of the thread
/// @param post The body of the thread
/// @param r_message The list of replies id of the thread
typedef struct thread_s {
    uuid_t id;
    time_t ctt;
    uuid_t owner;
    char *name;
    char *post;
    uuid_t *r_message;
} thread_t;

/// @brief Structure containing all the data of a message
/// @param id The unique identifier of the message
/// @param ctt The creation time of the message
/// @param t_client The sender client of the message (client_t)
/// @param r_client The receiver client/post of the message (client_t/thread_t)
/// @param msg The body of the message
typedef struct message_s {
    uuid_t id;
    time_t ctt;
    uuid_t t_client;
    uuid_t r_client;
    char *msg;
} message_t;

/// @brief Union containing all the data structures
/// @param client The client structure
/// @param team The team structure
/// @param channel The channel structure
/// @param thread The thread structure
/// @param message The message structure
typedef union data_u {
    client_t client;
    team_t team;
    channel_t channel;
    thread_t thread;
    message_t message;
} data_t;

/// @brief Structure containing the data to transfer
/// @param t_command The command to execute
/// @param p_size The size of the data to transfer
/// @param p_data The data to transfer (list or unary element(s))
/// @param p_extra The extra data to transfer, if needed
typedef struct transfer_s {
    char *t_command;
    unsigned int p_size;
    data_t *p_data;
    __attribute__((unused)) data_t p_extra;
} transfer_t;
