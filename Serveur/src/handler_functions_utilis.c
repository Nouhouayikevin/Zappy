/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** handler_functions_utilis
*/

#include "../include/my.h"
#include <stdio.h>
#include <stdarg.h>


void send_ebo_to_graphics(int sender_id,
    network_t *my_t)
{
    char buffer[1024] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "ebo %d\n", sender_id);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
    }
}

void send_pnw_to_graphics(int sender_id,
    network_t *my_t, slot_t *new_slot, team_t *a_team)
{
    char buffer[1024] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "ebo %d\n", sender_id);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1)
            dprintf(fd, "pnw %d %d %d %d %d %s\n", new_slot->id,
                new_slot->x, new_slot->y, new_slot->dir + 1,
                new_slot->level, a_team->team_name);
    }
}

//this function is to init a slot for a new player
static void init_slot(int id, slot_t **new_slot,
    team_t *a_team, network_t *my_t)
{
    if ((*new_slot)->state == EGG || (*new_slot)->id > 0)
        send_ebo_to_graphics(id, my_t);
    (*new_slot)->id = id;
    (*new_slot)->state = ALIVE;
    (*new_slot)->level = 1;
    (*new_slot)->resources[FOOD] = 10;
    for (int i = 1; i < 7; i++){
        (*new_slot)->resources[i] = 0;
    }
    (*new_slot)->dir = (int) random_num(0, 3);
    (*new_slot)->since_last = time(NULL);
    (*new_slot)->count = 0;
    send_pnw_to_graphics(id, my_t, *new_slot, a_team);
    send_pin_to_graphics(id, my_t, *new_slot);
}

void inner_add_player_loop(linked_list_t **a_slot, team_t *a_team)
{
    for ((*a_slot) = a_team->slots; (*a_slot) != NULL;
        (*a_slot) = (*a_slot)->next)
        if (((slot_t *)(*a_slot)->data)->state == EGG)
            break;
}

//This function is to add a new_player
int add_new_player(linked_list_t *team, int id, char *the_team,
    network_t *my_t)
{
    team_t *a_team = NULL;
    slot_t *new_slot = NULL;
    linked_list_t *a_slot = NULL;

    for (linked_list_t *temp = team; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        inner_add_player_loop(&a_slot, a_team);
        if (a_slot == NULL)
            break;
        new_slot = (slot_t *)a_slot->data;
        if (new_slot != NULL && !strcmp(a_team->team_name, the_team)){
            init_slot(id, &new_slot, a_team, my_t);
            a_team->available_slot--;
            new_slot->state = ALIVE;
            return a_team->available_slot;
        }
    }
    return -1;
}

static void printer(slot_t *a_player, network_t *my_t, team_t *a_team, int id)
{
    dprintf(GID, "pnw %d %d %d %d %d %s\n", a_player->id,
    MI, MJ, a_player->dir + 1, a_player->level, a_team->team_name);
    dprintf(GID, "ppo %d %d %d %d\n", a_player->id, MI,
        MJ, a_player->dir + 1);
    dprintf(GID, "pin %d %d %d %ld %ld %ld %ld %ld %ld %ld\n",
    a_player->id, MI, MJ, AR[FOOD], AR[LINEMATE], AR[DERAUMERE],
    AR[SIBUR], AR[MENDIANE], AR[PHIRAS], AR[THYSTAME]);
}

static void graphic_welcomer(linked_list_t *team, int id, char *the_team,
    network_t *my_t)
{
    slot_t *a_player = NULL;
    team_t *a_team = NULL;
    team_t *my_team = NULL;

    for (linked_list_t *temp = my_t->w->list_of_player; temp != NULL;
        temp = temp->next){
        a_player = (slot_t *)temp->data;
        if (a_player->state == ALIVE){
            a_team = get_player_team(team, a_player->id);
            printer(a_player, my_t, a_team, id);
        }
    }
}

static void graphic_action(linked_list_t *team, int id,
    network_t *my_t, char *the_team)
{
    tile_t *w = NULL;

    dprintf(GID, "msz %d %d\n",
        my_t->my_params.width, my_t->my_params.heigth);
    for (linked_list_t *a_team = team; a_team != NULL; a_team = a_team->next)
        dprintf(GID, "tna %s\n", ((team_t *) a_team->data)->team_name);
    for (int i = 0; i < my_t->my_params.heigth; i++){
        for (int j = 0; j < my_t->my_params.width; j++){
            w = &my_t->world_map[i][j];
            dprintf(GID, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n",
            i, j, WR[FOOD], WR[LINEMATE],
                WR[DERAUMERE], WR[SIBUR], WR[MENDIANE],
                WR[PHIRAS], WR[THYSTAME]);
            my_t->w = w;
            my_t->i = i;
            my_t->j = j;
            graphic_welcomer(team, id, the_team, my_t);
        }
    }
}

int add_player(linked_list_t *team, int id, char *the_team, network_t *my_t)
{
    team_t *a_team = NULL;
    slot_t *new_slot = NULL;
    linked_list_t *a_slot = NULL;
    int add_return = 0;
    tile_t *w = NULL;
    int *t;

    if (!strncmp(the_team, "GRAPHIC", 7)){
        t = malloc(sizeof(int) * 2);
        t[0] = my_t->handler[id].fd;
        push_in_list(t, &my_t->graphics_id);
        graphic_action(team, id, my_t, the_team);
        return -1;
    }
    add_return = add_new_player(team, id, the_team, my_t);
    if (add_return >= 0)
        return add_return;
    close(my_t->handler[id].fd);
    my_t->handler[id].fd = -1;
    return -1;
}
