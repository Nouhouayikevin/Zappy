/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** get_player_slot
*/

#include "../include/my.h"

slot_t *get_player_slot(linked_list_t *teams, int id)
{
    bool find_it = false;
    team_t *a_team = NULL;

    for (linked_list_t *temp = teams; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        if (a_team->slots == NULL)
            continue;
        find_it = check_user_in_team(a_team->slots, id);
        if (find_it)
            return check_user_in_slot(a_team->slots, id);
    }
    return NULL;
}
