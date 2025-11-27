/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** actions
*/

#include "../include/my.h"

void forward_action(slot_t *player, network_t *my_t)
{
    if (player->dir == NORTH)
        player->x--;
    if (player->dir == EAST)
        player->y++;
    if (player->dir == WEST)
        player->y--;
    if (player->dir == SOUTH)
        player->x++;
    if (player->x == my_t->my_params.width)
        player->x = 0;
    if (player->x < 0)
        player->x = my_t->my_params.width - 1;
    if (player->y == my_t->my_params.heigth)
        player->y = 0;
    if (player->y < 0)
        player->y = my_t->my_params.heigth - 1;
}

void left_action(slot_t *player)
{
    bool done = false;

    if (player->dir == NORTH){
        player->dir = WEST;
        done = true;
    }
    if (player->dir == WEST && !done){
        player->dir = SOUTH;
        done = true;
    }
    if (player->dir == SOUTH && !done){
        player->dir = EAST;
        done = true;
    }
    if (player->dir == EAST && !done)
        player->dir = NORTH;
}

void right_action(slot_t *player)
{
    bool done = false;

    if (player->dir == NORTH && done == false){
        player->dir = EAST;
        done = true;
    }
    if (player->dir == EAST && !done){
        player->dir = SOUTH;
        done = true;
    }
    if (player->dir == SOUTH && !done){
        player->dir = WEST;
        done = true;
    }
    if (player->dir == WEST && !done)
        player->dir = NORTH;
}

int total_alive_func(linked_list_t *players)
{
    slot_t *player = NULL;
    int count = 0;

    for (linked_list_t *temp = players; temp != NULL; temp = temp->next){
        player = (slot_t *)temp->data;
        if (player == NULL)
            continue;
        if (player->state == ALIVE)
            count++;
    }
    return count;
}

void right(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *player_slot = get_player_slot(teams, id);

    printf("exec Right\n");
    move(player_slot, my_t, RIGHT);
    write(my_t->handler[player_slot->id].fd, "ok\n", 3);
}
