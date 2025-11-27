/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** right_left_keeper
*/

#include "../include/my.h"
void resources_inner_loop(int temp, int i, char *look_available)
{
    bool s = false;

    while (temp > 0){
        if (strlen(look_available) > 0)
            s = true;
        if (s && look_available[strlen(look_available) - 1] != ' '
            && look_available[strlen(look_available) - 1] != '[')
            strcat(look_available, " ");
        resource_writer(i, look_available);
        temp--;
    }
}

void checker(network_t *my_t, int x, int y, char *look_available)
{
    for (int n = total_alive_func(WL); n > 0; n--){
        if (n < total_alive_func(WL))
            strcat(look_available, " ");
        strcat(look_available, "player");
    }
}

void resources_ew(network_t *my_t, char *look_available, int y, slot_t *p)
{
    int temp = 0;

    for (int x = my_t->start; my_t->count < (my_t->count_size * 2 + 1) ||
        my_t->count_size == 0; x++){
        if (x > my_t->my_params.width - 1)
            x = 0;
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

bool check_user_in_team_spec(linked_list_t *slots, int id, int x, int y)
{
    slot_t *a_slot = NULL;

    for (linked_list_t *temp = slots; temp != NULL; temp = temp->next){
        a_slot = (slot_t *)(temp->data);
        if (a_slot == NULL)
            continue;
        if (a_slot->id == id && a_slot->x == x && a_slot->y == y)
            return true;
    }
    return false;
}

bool check_user_in_team(linked_list_t *slots, int id)
{
    slot_t *a_slot = NULL;

    for (linked_list_t *temp = slots; temp != NULL; temp = temp->next){
        a_slot = (slot_t *)(temp->data);
        if (a_slot == NULL)
            continue;
        if (a_slot->id == id)
            return true;
    }
    return false;
}
