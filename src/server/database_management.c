/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** database_loading_management.c
*/

#include "server/data_utils.h"
#include "server/database_utils.h"
#include <stdio.h>
#include <unistd.h>

static const load_tab_t load_tab[] = {
    {CLIENTS, &load_clients},
    {DISCUSSIONS, &load_messages},
    {TEAMS, &load_teams},
    {CHANNELS, &load_channels},
    {THREADS, &load_threads},
    {NONE, NULL}
};

static const char *db_paths[] = {
    "database/clients",
    "database/discussions",
    "database/teams",
    "database/channels",
    "database/threads",
    NULL
};

static db_depth_t check_empty_database_file(int i)
{
    FILE *fd = NULL;

    printf("Checking %s\n", db_paths[i]);
    fd = fopen(db_paths[i], "r");
    if (!feof(fd)) {
        fclose(fd);
        return i;
    } else {
        fclose(fd);
        return -1;
    }
}

db_depth_t check_database(void)
{
    for (int i = 0; db_paths[i]; i++) {
        if (access(db_paths[i], F_OK) == -1 && i == 0) {
            return -1;
        }
        if (access(db_paths[i], F_OK) == -1) {
            return check_empty_database_file(i - 1);
        }
    }
    return -1;
}

int load_database(server_t *serv, db_depth_t db_depth)
{
    int ret = 0;

    for (int i = 0; load_tab[i].load; i++) {
        if (load_tab[i].type > db_depth) {
            break;
        }
        ret = load_tab[i].load(serv);
        if (ret == SYSTEM_ERROR) {
            return SYSTEM_ERROR;
        }
    }
    return SYSTEM_OK;
}
