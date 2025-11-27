/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** incantation
*/

#include "../include/my.h"

const int elevation_requirements[7][7] = {
    {1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 2},
    {2, 0, 1, 0, 2, 0, 2},
    {1, 1, 2, 0, 1, 0, 4},
    {1, 2, 1, 3, 0, 0, 4},
    {1, 2, 3, 0, 1, 0, 6},
    {2, 2, 2, 2, 2, 1, 6}
};

void sot_pot(int fd, char *buffer, linked_list_t *g)
{
    fd = *((int *)g->data);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
}

static void send_pic(tile_t *tile, int level,
    linked_list_t *teams, network_t *my_t)
{
    char buffer[1024] = {0};
    char line[64] = {0};
    linked_list_t *p = tile->list_of_player;
    slot_t *pl = NULL;
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "pic %d %d %d",
        tile->x, tile->y, level);
    while (p) {
        pl = (slot_t *)p->data;
        if (pl->level == level && pl->state == ALIVE) {
            snprintf(line, sizeof(line), " #%d", pl->id);
            strncat(buffer, line, sizeof(buffer) - strlen(buffer) - 1);
        }
        p = p->next;
    }
    strncat(buffer, "\n", sizeof(buffer) - strlen(buffer) - 1);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next)
        sot_pot(fd, buffer, g);
}

bool can_incant(tile_t *tile, int level, int type)
{
    const int *req = NULL;
    int players_needed = 0;
    int count = 0;
    slot_t *pl = NULL;

    if (level < 1 || level > 7)
        return false;
    req = elevation_requirements[level - 1];
    players_needed = req[6];
    for (linked_list_t *p = tile->list_of_player; p; p = p->next) {
        pl = (slot_t *)p->data;
        if (pl->level == level && pl->state == type)
            count++;
    }
    if (count < players_needed)
        return false;
    for (int i = 0; i < 6; i++)
        if (tile->resources[i + 1] < (size_t)req[i])
            return false;
    return true;
}

static void send_pie(int x, int y, int success, network_t *my_t)
{
    char buffer[128] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "pie %d %d %d\n", x, y, success);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
    }
}

void send_plv(network_t *my_t, int id, int level)
{
    char buffer[128] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "plv %d %d\n", id, level);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
    }
}

int incantation(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *player = get_player_slot(teams, id);
    tile_t *tile = NULL;
    slot_t *pl = NULL;

    if (!player)
        return -1;
    tile = &my_t->world_map[player->x][player->y];
    if (!can_incant(tile, player->level, ALIVE)) {
        write(my_t->handler[id].fd, "ko\n", 3);
        return -2;
    }
    write(my_t->handler[id].fd, "Elevation underway\n", 19);
    for (linked_list_t *p = tile->list_of_player; p; p = p->next) {
        pl = (slot_t *)p->data;
        if (pl->level == player->level && pl->state == ALIVE)
            pl->state = INCANTATION;
    }
    send_pic(tile, player->level, teams, my_t);
    return INCANTATION_FUN;
}

static void can_incant_action(tile_t *tile, slot_t *player, network_t *my_t)
{
    slot_t *pl = NULL;

    for (linked_list_t *p = tile->list_of_player; p; p = p->next) {
        pl = (slot_t *)p->data;
        if (pl->level == player->level && pl->state == INCANTATION)
            pl->state = ALIVE;
    }
    write(my_t->handler[player->id].fd, "ko\n", 3);
}

static void inner_exec_incantation(slot_t **pl, slot_t *player,
    network_t *my_t)
{
    if ((*pl)->level == player->level && (*pl)->state == INCANTATION) {
        (*pl)->level += 1;
        (*pl)->state = ALIVE;
        dprintf(my_t->handler[player->id].fd, "Current level: %d\n",
            (*pl)->level);
    }
}

static void remove_loop(tile_t *tile, const int *req)
{
    for (int i = 0; i < 6; i++)
        tile->resources[i + 1] -= req[i];
}

void exec_incantation(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *player = get_player_slot(teams, id);
    tile_t *tile = NULL;
    const int *req = NULL;
    slot_t *pl = NULL;

    if (!player)
        return;
    tile = &my_t->world_map[player->x][player->y];
    req = elevation_requirements[player->level - 1];
    if (!can_incant(tile, player->level, INCANTATION)) {
        can_incant_action(tile, player, my_t);
        return;
    }
    for (linked_list_t *p = tile->list_of_player; p; p = p->next) {
        pl = (slot_t *)p->data;
        inner_exec_incantation(&pl, player, my_t);
    }
    send_pie(player->x, player->y, player->level, my_t);
    send_plv(my_t, id, player->level);
    remove_loop(tile, req);
}
