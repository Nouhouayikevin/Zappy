/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** team_creator
*/

#include "../include/my.h"

static void init_team(team_t **temp, params_t my_params, int i)
{
    *temp = malloc(sizeof(team_t));
    (*temp)->total_slot = my_params.client_num;
    (*temp)->available_slot = my_params.client_num;
    (*temp)->team_name = strdup(my_params.user_name[i]);
    (*temp)->slots = NULL;
}

//This function is for the first team creation
linked_list_t *create_team(params_t my_params, tile_t **worldmap)
{
    linked_list_t *team = NULL;
    team_t *temp = NULL;
    slot_t *player = NULL;

    for (int i = 0; my_params.user_name[i] != NULL; i++){
        init_team(&temp, my_params, i);
        for (int j = 0; j < my_params.client_num; j++){
            player = malloc(sizeof(slot_t));
            player->x = random_num(0, my_params.heigth - 1);
            player->y = random_num(0, my_params.width - 1);
            player->state = EGG;
            player->id = 0;
            player->level = 0;
            push_in_list(player, &temp->slots);
            worldmap[player->x][player->y].num_of_player++;
            push_in_list(player, &WMP);
        }
        push_in_list(temp, &team);
    }
    return team;
}
