/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** client.c
*/

// #include <errno.h>
// #include <string.h>
// #include <signal.h>
// #include <limits.h>
// #include <libgen.h>
// #include <fcntl.h>
// #include <sys/wait.h>
#include "client/client.h"

int main(int ac, char **av)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;

    if (ac != 3)
        return 84;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(av[1]);
    servaddr.sin_port = htons(atoi(av[2]));
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))
        return 84;
    user_t user;
    user.size = 524;
    user.nb_buf = 0;
    user.stdin_fd = fileno(stdin);
    user.sockfd = sockfd;
    send_messages(user);
    close(sockfd);
    return 0;
}
