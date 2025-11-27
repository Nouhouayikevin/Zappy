/*
** EPITECH PROJECT, 2025
** network
** File description:
** network
*/

#include "../include/my.h"
network_t *memory;
int main(int ac, char **av)
{
    network_t my_t;
    params_t my_params;
    tile_t **worlmap;
    linked_list_t *players = NULL;

    srand(time(NULL));
    my_params.freq = DEFAULT_FREQ;
    my_params = params_getter(av, ac);
    memory = &my_t;
    worlmap = empty_world(my_params.heigth, my_params.width);
    functions_init(&my_t);
    resource_array(my_params.heigth, my_params.width, worlmap, &my_t);
    players = create_team(my_params, worlmap);
    init_network_t(my_params, &my_t, av, worlmap);
    init_binding(my_t.sfd, my_t.address, &my_t, av);
    while (1){
        poll(my_t.handler, my_t.total_fd, 2000);
        wait_event(&my_t, players, my_params);
    }
    return 0;
}
