/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** init_my_network_structure
*/

#include "../include/my.h"
void init_network_t(params_t my_params, network_t *my_t, char **av,
    tile_t **worldmap)
{
    int size = 0;

    for (size = 0; my_params.user_name[size] != NULL; size++);
    my_t->handler = malloc(sizeof(struct pollfd) * ((size *
        my_params.client_num) + 1));
    my_t->total_fd = (size * my_params.client_num) + 1;
    my_t->my_params = my_params;
    my_t->world_map = worldmap;
    my_t->queue = NULL;
    my_t->sfd = socket(AF_INET, SOCK_STREAM, 0);
    my_t->address = init_socker(*my_t, av);
}
