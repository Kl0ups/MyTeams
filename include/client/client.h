/*
** EPITECH PROJECT, 2024
** client
** File description:
** client
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <strings.h>
#include <string.h>
#include "common_utils.h"

int send_messages(int);
const char *str_id(uuid_t id);
int handle_display_command6(char *, transfer_t);
int handle_display_command5(char *, transfer_t);
int handle_display_command4(char *, transfer_t);
int handle_display_command3(char *, transfer_t);
int handle_display_command2(char *, transfer_t);
