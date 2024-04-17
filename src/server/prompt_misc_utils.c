/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** prompt_misc_utils.c
*/

#include <stdio.h>

int prompt_help(void)
{
    puts("USAGE: ./myteams_server port\n");
    puts("\tport\tis the port number on which the server socket listens");
    return 0;
}
