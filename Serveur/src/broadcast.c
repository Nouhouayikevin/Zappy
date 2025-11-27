/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** broadcast
*/

#include "../include/my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

static void send_pbc_to_graphics(int sender_id, const char *msg,
    network_t *my_t)
{
    char buffer[1024] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "pbc %d %s\n", sender_id, msg);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
    }
}

static int wrap_distance(int a, int b, int max)
{
    int diff = b - a;

    if (abs(diff) > max / 2) {
        if (diff > 0)
            return diff - max;
        return diff + max;
    }
    return diff;
}

static int get_relative_direction(int dx, int dy)
{
    if (dx == 0 && dy < 0)
        return 1;
    if (dx > 0 && dy < 0)
        return 2;
    if (dx > 0 && dy == 0)
        return 3;
    if (dx > 0 && dy > 0)
        return 4;
    if (dx == 0 && dy > 0)
        return 5;
    if (dx < 0 && dy > 0)
        return 6;
    if (dx < 0 && dy == 0)
        return 7;
    if (dx < 0 && dy < 0)
        return 8;
    return 0;
}

static int rotate_direction(int dir, int orientation)
{
    static const int offsets[4] = {0, 2, 4, 6};
    int offset = 0;

    if (orientation >= 0 && orientation <= 3)
        offset = offsets[orientation];
    dir += offset;
    if (dir > 8)
        dir -= 8;
    return dir;
}

static int compute_direction(slot_t *sender, slot_t *receiver, params_t p)
{
    int dx = wrap_distance(sender->x, receiver->x, p.width);
    int dy = wrap_distance(sender->y, receiver->y, p.heigth);
    int raw_dir = get_relative_direction(dx, dy);

    if (raw_dir == 0)
        return 0;
    return rotate_direction(raw_dir, receiver->dir);
}

static bool should_skip_player(slot_t *sender, slot_t *receiver)
{
    return receiver->id == sender->id || receiver->state != ALIVE;
}

static void send_broadcast_to(slot_t *receiver, slot_t *sender,
    char *msg, network_t *my_t)
{
    int k = compute_direction(sender, receiver, my_t->my_params);

    dprintf(my_t->handler[receiver->id].fd,
        "message %d, %s\n", k, msg);
}

static void send_broadcast_to_team(slot_t *sender, char *msg,
    team_t *team, network_t *my_t)
{
    linked_list_t *s = NULL;
    slot_t *receiver = NULL;

    for (s = team->slots; s; s = s->next) {
        receiver = (slot_t *)s->data;
        if (should_skip_player(sender, receiver))
            continue;
        send_broadcast_to(receiver, sender, msg, my_t);
    }
}

static void send_to_all(slot_t *sender, char *msg,
    linked_list_t *teams, network_t *my_t)
{
    linked_list_t *t = NULL;
    team_t *team = NULL;

    for (t = teams; t; t = t->next) {
        team = (team_t *)t->data;
        send_broadcast_to_team(sender, msg, team, my_t);
    }
}

void broadcast(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *sender = get_player_slot(teams, id);
    char *msg = NULL;

    if (!sender)
        return;
    msg = strstr(my_t->request, " ");
    if (!msg || strlen(msg + 1) < 1) {
        write(my_t->handler[id].fd, "ko\n", 3);
        return;
    }
    msg++;
    send_to_all(sender, msg, teams, my_t);
    send_pbc_to_graphics(sender->id, msg, my_t);
    write(my_t->handler[id].fd, "ok\n", 3);
}
