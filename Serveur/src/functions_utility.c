/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** functions_utility
*/

#include "../include/my.h"

void resource_writer(int i, char *look_available)
{
    if (i == FOOD)
        strcat(look_available, "food");
    if (i == SIBUR)
        strcat(look_available, "sibur");
    if (i == LINEMATE)
        strcat(look_available, "linemate");
    if (i == THYSTAME)
        strcat(look_available, "thystame");
    if (i == DERAUMERE)
        strcat(look_available, "deraumere");
    if (i == MENDIANE)
        strcat(look_available, "mendiane");
    if (i == PHIRAS)
        strcat(look_available, "phiras");
}

void northen_southen(network_t *my_t, char *look_available, slot_t *p)
{
    for (int x = p->x; my_t->level <= p->level;){
        my_t->start = p->y - my_t->count_size;
        my_t->end = p->y + my_t->count_size;
        if (x < 0)
            x = my_t->my_params.width - 1;
        if (x > my_t->my_params.width - 1)
            x = 0;
        if (my_t->start < 0)
            my_t->start = my_t->my_params.width - 1 - my_t->start;
        if (my_t->end > my_t->my_params.width - 1)
            my_t->end = my_t->end - my_t->my_params.width;
        my_t->count = 0;
        resources_sh(my_t, look_available, x, p);
        if (my_t->level + 1 <= p->level)
            strcat(look_available, ", ");
        my_t->count_size++;
        my_t->level++;
        x += my_t->dir;
    }
}

void east_westen(network_t *my_t, char *look_available, slot_t *p)
{
    printf("east western\n");
    for (int y = p->y; my_t->level <= p->level;){
        my_t->start = p->x - my_t->count_size;
        my_t->end = p->x + my_t->count_size;
        if (y < 0)
            y = my_t->my_params.width - 1;
        if (y > my_t->my_params.width - 1)
            y = 0;
        if (my_t->start < 0)
            my_t->start = my_t->my_params.heigth - 1 - my_t->start;
        if (my_t->end > my_t->my_params.heigth - 1)
            my_t->end = my_t->end - my_t->my_params.heigth;
        my_t->count = 0;
        resources_ew(my_t, look_available, y, p);
        if (my_t->level + 1 <= p->level)
            strcat(look_available, ", ");
        my_t->count_size++;
        my_t->level++;
        y += my_t->dir;
    }
}

void resources_ew_inner_loop(char *look_available, network_t *my_t,
    int x, int y)
{
    for (int i = 0; i < 7; i++)
        if (my_t->world_map[x][y].resources[i] > 0)
            resource_writer(i, look_available);
}

void resources_sh(network_t *my_t, char *look_available, int x, slot_t *p)
{
    int temp = 0;

    for (int y = my_t->start; my_t->count < (my_t->count_size * 2 + 1) ||
        my_t->count_size == 0; y++){
        if (y > my_t->my_params.width - 1)
            y = 0;
        if (my_t->count > 0)
            strcat(look_available, ",");
        checker(my_t, x, y, look_available);
        for (int i = 0; i < 7; i++){
            temp = my_t->world_map[x][y].resources[i];
            resources_inner_loop(temp, i, look_available);
        }
        if (!my_t->count_size)
            break;
        my_t->count++;
    }
}
