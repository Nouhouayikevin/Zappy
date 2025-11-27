/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** command_handler
*/

#include "../include/my.h"
//This function is to check if a user is in specific team
slot_t *check_user_in_slot(linked_list_t *slots, int id)
{
    slot_t *a_slot = NULL;

    for (linked_list_t *temp = slots; temp != NULL; temp = temp->next){
        a_slot = (slot_t *)(temp->data);
        if (a_slot->id == id)
            return a_slot;
    }
    return NULL;
}

//This function is to check if a user is already authentificate
//or not
bool already_user(int id, linked_list_t *team)
{
    bool find_it = false;
    team_t *a_team = NULL;

    for (linked_list_t *temp = team; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        if (a_team->slots == NULL)
            continue;
        find_it = check_user_in_team(a_team->slots, id);
        if (find_it)
            return find_it;
    }
    return false;
}

//This function is to check if the mentionnned team is a good one
bool is_valid_team(char *the_team, linked_list_t *team)
{
    team_t *a_team = NULL;

    if (!strcmp(the_team, "GRAPHIC"))
        return true;
    for (linked_list_t *temp = team; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        printf("in valid = %s\n", a_team->team_name);
        printf("a team = %s;\n", the_team);
        if (!strcmp(a_team->team_name, the_team)){
            printf("valid\n");
            return true;
        }
    }
    return false;
}

static void gui_disconnection(network_t *my_t, int id)
{
    int count = 0;

    for (linked_list_t *t = my_t->graphics_id; t; t = t->next){
        if (*((int *)t->data) == id)
            delete_from_list(count, &t);
        count++;
    }
}

void void_disconnect_action(network_t *my_t, int id,
    linked_list_t *team, params_t my_params)
{
    int pos_t = 0;
    int pos = 0;
    slot_t *player_slot = NULL;
    team_t *player_team = NULL;

    close(my_t->handler[id].fd);
    my_t->handler[id].fd = -1;
    player_slot = get_player_slot(team, id);
    if (player_slot == NULL){
        gui_disconnection(my_t, id);
        return;
    }
    player_team = get_player_team(team, id);
    pos = find_player_pos_int_world(my_t, player_slot);
    pos_t = find_player_pos_in_the_slots(my_t, id, player_team->slots);
    delete_without_free_from_list(pos_t, &player_team->slots);
    my_t->world_map[player_slot->x][player_slot->y].num_of_player--;
    delete_without_free_from_list(pos,
    &my_t->world_map[player_slot->x][player_slot->y].list_of_player);
    player_slot->state = INACTIVE;
}

void command_handler(network_t *my_t, int id, linked_list_t *team,
    params_t my_params)
{
    char temp[BUFSIZ];
    int count_read = -1;
    int team_available_slot = 0;

    count_read = read(my_t->handler[id].fd, &temp, BUFSIZ);
    if (count_read == 0 || count_read == -1){
        if (count_read == -1)
            return;
        void_disconnect_action(my_t, id, team, my_params);
        return;
    }
    temp[count_read - 1] = '\0';
    if (!already_user(id, team) && is_valid_team(temp, team)){
        if (add_player(team, id, temp, my_t) == -1)
            return;
        send_connect_nbr(team, id, temp, my_t);
        send_world_size(my_t, id, my_params);
    } else if (already_user(id, team))
        exec_instruction_part(team, id, temp, my_t);
}
