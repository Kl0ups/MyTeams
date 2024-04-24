/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** command_utils.c
*/

#include "server/data_utils.h"
#include <string.h>
#include <stdlib.h>

static int count_args(char **args)
{
    int i = 0;

    if (args == NULL)
        return 0;
    while (args[i] != NULL)
        i++;
    return i;
}

char **get_cmd_args(const char *cmd_buffer)
{
    char *cmd = strdup(cmd_buffer);
    char *token = NULL;
    char **args = NULL;

    token = strtok(cmd, " ");
    args = malloc(sizeof(char *));
    args = NULL;
    if (args == NULL)
        return NULL;
    while (token != NULL) {
        args = realloc(args, sizeof(char *) * (count_args(args) + 2));
        if (args == NULL)
            return NULL;
        args[count_args(args)] = strdup(token);
        args[count_args(args) + 1] = NULL;
        token = strtok(NULL, " ");
    }
    return args;
}
