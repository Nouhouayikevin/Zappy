/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** usage
*/

#include "../include/my.h"

void show_my_usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height");
    printf("-n name1 name2 ... -c clientsNb -f freq\n");
}

void send_pgt_to_graphics(int id,
    network_t *my_t, slot_t *p, int res)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "pgt %d %d\n", id, res);
            dprintf(fd, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n", p->x,
            p->y, PR[FOOD], PR[LINEMATE], PR[DERAUMERE],
            PR[SIBUR], PR[MENDIANE], PR[PHIRAS], PR[THYSTAME]);
        }
    }
}

void take(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *p = get_player_slot(teams, id);
    int which_res = identifier_resources(my_t->request_tab[1]);

    if (my_t->world_map[p->x][p->y].resources[which_res] > 0){
        p->resources[which_res]++;
        my_t->world_map[p->x][p->y].resources[which_res]--;
        write(my_t->handler[id].fd, "ok\n", 3);
        send_pgt_to_graphics(id, my_t, p, which_res);
        send_pin_to_graphics(id, my_t, p);
    } else
        write(my_t->handler[id].fd, "ko\n", 3);
}

void send_sgt_to_graphic(network_t *my_t)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g != NULL; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "sgt %d\n", my_t->my_params.freq);
        }
    }
}

void send_bct_to_graphics(network_t *my_t, int x, int y)
{
    char buffer[1024] = {0};
    int fd = 0;

    for (linked_list_t *g = my_t->graphics_id; g != NULL; g = g->next) {
        fd = *((int *)g->data);
        if (fd != -1){
            dprintf(fd, "bct %d %d %ld %ld %ld %ld %ld %ld %ld\n", x,
            y, RI[FOOD], RI[LINEMATE], RI[DERAUMERE],
            RI[SIBUR], RI[MENDIANE], RI[PHIRAS], RI[THYSTAME]);
        }
    }
}
