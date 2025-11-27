/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** another_function
*/

#include "../include/my.h"

void send_ppo_to_graphics(int sender_id,
    network_t *my_t, team_t *the_team, slot_t *p)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1)
            dprintf(fd, "ppo %d %d %d %d\n", p->id, p->x,
        p->y, p->dir + 1);
    }
}

void move(slot_t *player, network_t *my_t, int command)
{
    int pos = find_player_pos_int_world(my_t, player);

    if (command == FORWARD){
        my_t->world_map[player->x][player->y].num_of_player--;
        delete_without_free_from_list(pos,
        &my_t->world_map[player->x][player->y].list_of_player);
        forward_action(player, my_t);
        my_t->world_map[player->x][player->y].num_of_player++;
        push_in_list(player,
            &my_t->world_map[player->x][player->y].list_of_player);
        send_ppo_to_graphics(player->id, my_t, NULL, player);
    }
    if (command == LEFT)
        left_action(player);
    if (command == RIGHT)
        right_action(player);
}

void forward(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *player_slot = get_player_slot(teams, id);

    printf("exec Forward\n");
    printf("old x = %d and old y = %d\n", player_slot->x, player_slot->y);
    move(player_slot, my_t, FORWARD);
    write(my_t->handler[player_slot->id].fd, "ok\n", 3);
    printf("new x = %d and new y = %d\n", player_slot->x, player_slot->y);
}

void left(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *player_slot = get_player_slot(teams, id);

    printf("exec Left\n");
    move(player_slot, my_t, LEFT);
    write(my_t->handler[player_slot->id].fd, "ok\n", 3);
}

static void send_enw_to_graphics(int sender_id,
    network_t *my_t, team_t *the_team, slot_t *p)
{
    char buffer[1024] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "enw %d %d %d %d\n",
        the_team->available_slot + sender_id + p->x + p->y,
        sender_id, p->x, p->y);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1) {
            dprintf(fd, "pfk %d\n", sender_id);
            write(fd, buffer, strlen(buffer));
        }
    }
}

void fork_f(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *p = get_player_slot(teams, id);
    slot_t *egg = malloc(sizeof(slot_t));
    team_t *a_team = get_player_team(teams, id);

    printf("exec fork\n");
    egg->state = EGG;
    egg->id = 0;
    if (my_t->graphics_id != NULL)
        egg->id = a_team->available_slot + id + p->x + p->y;
    egg->x = p->x;
    egg->y = p->y;
    push_in_list(egg, &a_team->slots);
    my_t->world_map[egg->x][egg->y].num_of_player++;
    push_in_list(egg,
        &my_t->world_map[egg->x][egg->y].list_of_player);
    write(my_t->handler[id].fd, "ok\n", 3);
    a_team->available_slot++;
    send_enw_to_graphics(id, my_t, a_team, p);
}
