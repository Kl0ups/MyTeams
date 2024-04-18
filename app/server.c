/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server.c
*/
#include "server/data_utils.h"
#include "server/launch_utils.h"
#include <stdlib.h>
#include <unistd.h>

int main(int ac, const char *av[])
{
    int port = -1;

    if (ac != 2)
        return (84);
    port = (int)strtol(av[1], NULL, 10);
    if (port < 0)
        return (84);
    return (teams_server(port));
}
