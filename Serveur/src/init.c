/*
** EPITECH PROJECT, 2025
** network
** File description:
** network
*/

#include "../include/my.h"

struct sockaddr_in init_socker(network_t my_t, char **av)
{
    int opt = 1;

    if (setsockopt(my_t.sfd, SOL_SOCKET, SO_REUSEADDR, &opt,
    sizeof(opt)) != 0){
        printf("Echec de paramètrage: %s\n", strerror(errno));
        exit(84);
    }
    my_t.address.sin_family = AF_INET;
    my_t.address.sin_addr.s_addr = INADDR_ANY;
    my_t.address.sin_port = htons(PORT);
    return my_t.address;
}

static void connection_action(network_t *my_t, char **av)
{
    for (int total = 1; total < my_t->total_fd; total++){
        my_t->handler[total].fd = -1;
        my_t->handler[total].events = 0;
        my_t->handler[total].revents = 0;
    }
    printf("Serving to the Anonymous user.\n");
}

void init_binding(int socketfd, addr_t address, network_t *my_t, char **av)
{
    int listening;
    int binding = bind(socketfd, (struct sockaddr*)&address,
    sizeof(address));

    if (binding < 0) {
        perror("bind failed");
        exit(84);
    }
    my_t->handler[0].fd = socketfd;
    my_t->handler[0].events = POLLIN;
    my_t->handler[0].revents = 0;
    listening = listen(socketfd, my_t->total_fd);
    if (listening < 0) {
        perror("listen");
        exit(84);
    }
    connection_action(my_t, av);
}
