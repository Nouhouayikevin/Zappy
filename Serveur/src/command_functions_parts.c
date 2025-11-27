/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** command_functions_parts
*/

#include "../include/my.h"

void connect_nbr(int id, linked_list_t *teams, network_t *my_t)
{
    bool find_it = false;
    team_t *a_team = NULL;
    int total_active = 0;
    slot_t *a_slot = NULL;

    for (linked_list_t *temp = teams; temp != NULL; temp = temp->next){
        a_team = (team_t *)(temp->data);
        if (a_team->slots == NULL)
            continue;
        find_it = check_user_in_team(a_team->slots, id);
        total_active = 0;
        for (linked_list_t *temp = a_team->slots; temp != NULL;
            temp = temp->next){
            a_slot = (slot_t *)(temp->data);
            total_active += (a_slot != NULL && a_slot->state == ALIVE) ? 1 : 0;
        }
        if (find_it)
            break;
    }
    connect_sender(total_active, my_t, id);
}

//This function the toal number of availaible slot in the slots
int available_slot(int id, linked_list_t *teams, network_t *my_t)
{
    bool find_it = false;
    team_t *a_team = NULL;
    int av_slot = 0;
    slot_t *a_slot = NULL;

    for (linked_list_t *temp = teams; temp != NULL; temp = temp->next){
        av_slot = 0;
        a_team = (team_t *)(temp->data);
        if (a_team->slots == NULL)
            continue;
        a_slot = NULL;
        for (linked_list_t *temp = a_team->slots; temp != NULL;
            temp = temp->next){
            av_slot += ((slot_t *)temp->data != NULL &&
                ((slot_t *)temp->data)->state == EGG) ? 1 : 0;
        }
    }
    return av_slot;
}

void look(int id, linked_list_t *team, network_t *my_t)
{
    slot_t *p = get_player_slot(team, id);
    int count_size = 1;
    char look_available[(my_t->my_params.width *
    my_t->my_params.heigth) * 10 * 7];

    for (int i = 0; i < p->level; i++)
        count_size += count_size + 2;
    look_available[0] = '\0';
    my_t->dir = (p->dir == NORTH || p->dir == WEST) ? -1 : 1;
    my_t->count = 0;
    my_t->level = 0;
    strcat(look_available, "[");
    my_t->count_size = 0;
    if (p->dir == NORTH || p->dir == SOUTH)
        northen_southen(my_t, look_available, p);
    if (p->dir == EAST || p->dir == WEST)
        east_westen(my_t, look_available, p);
    strcat(look_available, "]\n");
    write(my_t->handler[id].fd, look_available, strlen(look_available));
}

void send_pin_to_graphics(int id,
    network_t *my_t, slot_t *p)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "pin %d %d %d %ld %ld %ld %ld %ld %ld %ld\n",
                p->id, p->x, p->y, PR[FOOD], PR[LINEMATE], PR[DERAUMERE],
            PR[SIBUR], PR[MENDIANE], PR[PHIRAS], PR[THYSTAME]);
        }
    }
}

static void send_pdr_to_graphics(int id,
    network_t *my_t, slot_t *p, int res)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "pdr %d %d\n", id, res);
            dprintf(fd, "bct %d %d %ld %ld %ld %ld %ld %ld %ld", p->x, p->y,
            p->resources[FOOD], p->resources[LINEMATE],
            p->resources[DERAUMERE],
            p->resources[SIBUR],
            p->resources[MENDIANE], p->resources[PHIRAS],
            p->resources[THYSTAME]);
        }
    }
}

void set(int id, linked_list_t *team, network_t *my_t)
{
    slot_t *p = get_player_slot(team, id);
    int which_res = identifier_resources(my_t->request_tab[1]);

    if (p->resources[which_res] > 0){
        p->resources[which_res]--;
        my_t->world_map[p->x][p->y].resources[which_res]++;
        write(my_t->handler[id].fd, "ok\n", 3);
        send_pdr_to_graphics(id, my_t, p, which_res);
        send_pin_to_graphics(id, my_t, p);
    } else
        write(my_t->handler[id].fd, "ko\n", 3);
}
