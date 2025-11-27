/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** generate_world_utils
*/

#include "../include/my.h"

void free_world(int x, int y, tile_t **world_map)
{
    for (int i = 0; i < x; i++)
        free(world_map[i]);
    free(world_map);
}
