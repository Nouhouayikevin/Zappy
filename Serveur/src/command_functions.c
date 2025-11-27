/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** command_functions
*/

#include "../include/my.h"
void inner_inventory_condition(char *size_msg, int i, slot_t *player_slot)
{
    char *the_int = NULL;

    if (i == FOOD)
        strcat(size_msg, "[food ");
    if (i == SIBUR)
        strcat(size_msg, ", sibur ");
    if (i == LINEMATE)
        strcat(size_msg, ", linemate ");
    if (i == THYSTAME)
        strcat(size_msg, ", thystame ");
    if (i == DERAUMERE)
        strcat(size_msg, ", deraumere ");
    if (i == MENDIANE)
        strcat(size_msg, ", mendiane ");
    if (i == PHIRAS)
        strcat(size_msg, ", phiras ");
    the_int = int_to_str(player_slot->resources[i]);
    strcat(size_msg, the_int);
    free(the_int);
}

void check_inventory(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *player_slot = get_player_slot(teams, id);
    char *size_msg = malloc(sizeof(char) * (LIMIT_INT_SIZE * 7 * 10) + 3);

    printf("exec invetory\n");
    size_msg[0] = '\0';
    for (int i = 0; i < 7; i++)
        inner_inventory_condition(size_msg, i, player_slot);
    strcat(size_msg, "]\n");
    write(my_t->handler[id].fd, size_msg, strlen(size_msg));
    free(size_msg);
}

void connect_sender(int total_active, network_t *my_t, int id)
{
    char *str = int_to_str(total_active);
    char to_send[strlen(str) + 2];

    strcpy(to_send, str);
    strcat(to_send, "\n");
    write(my_t->handler[id].fd, to_send, strlen(to_send));
    free(str);
}

//send edi to player
static void send_edi_to_graphics(int sender_id,
    network_t *my_t)
{
    char buffer[1024] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "edi %d\n", sender_id);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
    }
}

//This function aim to send the right message after eject
void egg_deleter(linked_list_t *teams, slot_t *a, slot_t *p, network_t *my_t)
{
    int count = 0;
    team_t *the_team = get_player_team_spec(teams, a->id, p->x, p->y);
    slot_t *a_u = NULL;

    for (linked_list_t *temp = the_team->slots; temp != NULL;
        temp = temp->next){
        a_u = (slot_t *)temp->data;
        if (a_u->x == a->x && a_u->y == a->y && a->id == a_u->id){
            printf("count = %d\n", count);
            send_edi_to_graphics(a->id, my_t);
            delete_without_free_from_list(count, &the_team->slots);
            the_team->available_slot--;
        }
        count++;
    }
}

static void send_pex_to_graphics(int sender_id,
    network_t *my_t)
{
    char buffer[1024] = {0};
    int fd = 0;

    snprintf(buffer, sizeof(buffer), "pex %d\n", sender_id);
    for (linked_list_t *g = my_t->graphics_id; g; g = g->next) {
        fd = *((int *)g->data);
        printf("fd = %d\n", fd);
        if (fd != -1)
            write(fd, buffer, strlen(buffer));
    }
}

//Eject other from your tile and destroy their eggs
void eject(int id, linked_list_t *teams, network_t *my_t)
{
    slot_t *p = get_player_slot(teams, id);
    int pos = 0;
    slot_t *a = NULL;

    if (my_t->world_map[p->x][p->y].num_of_player < 1){
        write(my_t->handler[id].fd, "ko\n", 3);
        return;
    }
    eject_loop(a, p, my_t, teams);
    send_pex_to_graphics(id, my_t);
    write(my_t->handler[id].fd, "ok\n", 3);
}
