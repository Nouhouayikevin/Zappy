/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** handle_cmd_in_queue
*/

#include "../include/my.h"

int list_size(linked_list_t *list)
{
    int i = 0;

    for (linked_list_t *temp = list; temp != NULL; temp = temp->next){
        i++;
    }
    return i;
}

void exec_last_instruction(network_t *my_t, linked_list_t *teams)
{
    cmd_t *last_cmd = give_me_the_last_cmd(my_t->queue);
    team_t *the_team = NULL;

    if (last_cmd != NULL){
        printf("exec\n");
        my_t->teams = teams;
        my_t->request_tab = last_cmd->tab;
        my_t->request = last_cmd->request;
        the_team = get_player_team(teams, last_cmd->player->id);
        printf("the team = %s and the cmd = %s\n", the_team->team_name,
            last_cmd->tab[0]);
        my_t->cmd[last_cmd->cmd](last_cmd->player->id, teams, my_t);
        printf("the last pos = %d\n", last_cmd->count);
        last_cmd->cmd = -1;
        last_cmd->player->count--;
    }
}

static void food_handler(slot_t *player, network_t *my_t)
{
    if (player->state == ALIVE && difftime(time(NULL), player->since_last)
        >= 126 / (double)my_t->my_params.freq){
        player->resources[FOOD]--;
        player->since_last = time(NULL);
    }
}

static void send_pdi_to_graphics(int id,
    network_t *my_t, slot_t *p)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "pdi %d\n", id);
        }
    }
}

static void send_seg_to_graphics(char *the_team,
    network_t *my_t)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "seg %s\n", the_team);
        }
    }
}

void handle_death_inner_condition(linked_list_t *teams, slot_t *player,
    network_t *my_t, team_t *a_team)
{
    for (linked_list_t *a_t = a_team->slots; a_t != NULL; a_t = a_t->next){
        player = (slot_t *)a_t->data;
        if (player == NULL || (slot_t *)a_t->data == NULL)
            break;
        if (player->state == EGG || player->state == INACTIVE)
            break;
        food_handler(player, my_t);
        if (player->state == ALIVE && difftime(time(NULL), my_t->last_respawn)
            >= 20 / (double)my_t->my_params.freq){
            my_t->last_respawn = time(NULL);
            resource_array(my_t->my_params.heigth,
                my_t->my_params.width, my_t->world_map, my_t);
        }
        if (player->state == ALIVE && player->resources[FOOD] == 0){
            write(my_t->handler[player->id].fd, "dead\n", 5);
            void_disconnect_action(my_t, player->id, teams, my_t->my_params);
            send_pdi_to_graphics(player->id, my_t, player);
        }
    }
}

void handle_death(linked_list_t *teams, network_t *my_t)
{
    team_t *a_team;
    slot_t *player;
    int num_eight = 0;

    printf("in handle death\n");
    for (linked_list_t *temp = teams; temp != NULL; temp = temp->next){
        a_team = (team_t *)temp->data;
        handle_death_inner_condition(teams, player, my_t, a_team);
    }
}
