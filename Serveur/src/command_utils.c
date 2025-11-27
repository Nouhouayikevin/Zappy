/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** command_utils
*/

#include "../include/my.h"
slot_t *get_user_slot(linked_list_t *slots, int id)
{
    slot_t *a_slot = NULL;
    int pos = 0;

    for (linked_list_t *temp = slots; temp != NULL; temp = temp->next){
        a_slot = (slot_t *)(temp->data);
        a_slot->pos = pos;
        if (a_slot->id == id)
            return a_slot;
        pos++;
    }
    return NULL;
}

team_t *get_player_team(linked_list_t *teams, int id)
{
    bool find_it = false;
    team_t *a_team = NULL;

    for (linked_list_t *temp = teams; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        if (a_team->slots == NULL)
            continue;
        find_it = check_user_in_team(a_team->slots, id);
        if (find_it)
            return a_team;
    }
    return NULL;
}

team_t *get_player_team_spec(linked_list_t *teams, int id, int x, int y)
{
    bool find_it = false;
    team_t *a_team = NULL;

    for (linked_list_t *temp = teams; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        if (a_team->slots == NULL)
            continue;
        find_it = check_user_in_team_spec(a_team->slots, id, x, y);
        if (find_it)
            return a_team;
    }
    return NULL;
}

int find_player_pos_in_the_slots(network_t *my_t, int id, linked_list_t *slot)
{
    slot_t *player_t = NULL;
    int pos = 0;
    bool find = false;

    for (linked_list_t *temp = slot; temp != NULL; temp = temp->next){
        player_t = (slot_t *)temp->data;
        if (player_t->id == id){
            find = true;
            break;
        }
        pos++;
    }
    if (find)
        return pos;
    else
        return -1;
}

static int return_type(int pos, bool find)
{
    if (find)
        return pos;
    else
        return -1;
}

int find_player_pos_int_world(network_t *my_t, slot_t *player)
{
    slot_t *player_t = NULL;
    int pos = 0;
    bool find = false;

    if (player == NULL)
        return -1;
    for (linked_list_t *temp = my_t->world_map[player->x]
        [player->y].list_of_player; temp != NULL; temp = temp->next){
        player_t = (slot_t *)temp->data;
        if (player_t == NULL)
            continue;
        if (player_t->id == player->id){
            find = true;
            break;
        }
        pos++;
    }
    return return_type(pos, find);
}
