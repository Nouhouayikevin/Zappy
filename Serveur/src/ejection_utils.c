/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** ejection_utils
*/

#include "../include/my.h"
void msg_sender(network_t *my_t, slot_t *a, int value)
{
    char to_send[15];
    char *temp = NULL;

    temp = int_to_str(value);
    to_send[0] = '\0';
    strcat(to_send, "eject: ");
    strcat(to_send, temp);
    strcat(to_send, "\n");
    write(my_t->handler[a->id].fd, to_send, strlen(to_send));
    free(temp);
}

void nouth_ejection(slot_t *p, network_t *my_t, slot_t *a)
{
    if (p->dir == NORTH && a->state != EGG){
        a->x--;
        a->x = (a->x < 0) ? my_t->my_params.heigth - 1 : a->x;
        push_in_list(a, &my_t->world_map[a->x][a->y].list_of_player);
        my_t->world_map[a->x][a->y].num_of_player++;
        if (a->dir == NORTH)
            msg_sender(my_t, a, 5);
        if (a->dir == SOUTH)
            msg_sender(my_t, a, 1);
        if (a->dir == EAST)
            msg_sender(my_t, a, 7);
        if (a->dir == WEST)
            msg_sender(my_t, a, 3);
    }
}

void south_ejection(slot_t *p, network_t *my_t, slot_t *a)
{
    if (p->dir == SOUTH && a->state != EGG){
        a->x++;
        a->x = (a->x > my_t->my_params.heigth - 1) ? 0 : a->x;
        push_in_list(a, &my_t->world_map[a->x][a->y].list_of_player);
        my_t->world_map[a->x][a->y].num_of_player++;
        if (a->dir == NORTH)
            msg_sender(my_t, a, 1);
        if (a->dir == SOUTH)
            msg_sender(my_t, a, 5);
        if (a->dir == EAST)
            msg_sender(my_t, a, 3);
        if (a->dir == WEST)
            msg_sender(my_t, a, 7);
    }
}

void west_ejection(slot_t *p, network_t *my_t, slot_t *a)
{
    if (p->dir == WEST && a->state != EGG){
        a->y--;
        a->y = (a->y < 0) ? my_t->my_params.width - 1 : a->y;
        push_in_list(a, &my_t->world_map[a->x][a->y].list_of_player);
        my_t->world_map[a->x][a->y].num_of_player++;
        if (a->dir == NORTH)
            msg_sender(my_t, a, 7);
        if (a->dir == SOUTH)
            msg_sender(my_t, a, 3);
        if (a->dir == EAST)
            msg_sender(my_t, a, 1);
        if (a->dir == WEST)
            msg_sender(my_t, a, 5);
    }
}

void east_ejection(slot_t *p, network_t *my_t, slot_t *a)
{
    if (p->dir == EAST && a->state != EGG){
            a->y++;
            a->y = (a->y > my_t->my_params.width - 1) ? 0 : a->y;
            push_in_list(a, &my_t->world_map[a->x][a->y].list_of_player);
            my_t->world_map[a->x][a->y].num_of_player++;
            if (a->dir == NORTH)
                msg_sender(my_t, a, 3);
            if (a->dir == SOUTH)
                msg_sender(my_t, a, 7);
            if (a->dir == EAST)
                msg_sender(my_t, a, 5);
            if (a->dir == WEST)
                msg_sender(my_t, a, 1);
        }
}
