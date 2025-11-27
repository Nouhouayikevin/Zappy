/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** fork_and_eject
*/

#include "../include/my.h"

void ejection(slot_t *p, network_t *my_t, slot_t *a)
{
    nouth_ejection(p, my_t, a);
    south_ejection(p, my_t, a);
    west_ejection(p, my_t, a);
    east_ejection(p, my_t, a);
}

void some_operation(int *pos, linked_list_t **a_slot,
    network_t *my_t, slot_t *p)
{
    *pos++;
    (*a_slot) = (*a_slot)->next;
    my_t->world_map[p->x][p->y].num_of_player--;
}

void little_operation(slot_t **a, slot_t *p, network_t *my_t, int pos)
{
    egg_deleter(my_t->teams, *a, p, my_t);
    delete_without_free_from_list(pos,
        &my_t->world_map[p->x][p->y].list_of_player);
    *a = NULL;
}

void next_iteration(int *pos, linked_list_t **a_slot)
{
    *pos++;
    *(a_slot) = (*a_slot)->next;
}

bool eject_loop(slot_t *a, slot_t *p, network_t *my_t, linked_list_t *teams)
{
    int pos = 0;
    linked_list_t *a_slot = my_t->world_map[p->x][p->y].list_of_player;

    while (my_t->world_map[p->x][p->y].num_of_player > 1 && a_slot){
        a = (slot_t *)a_slot->data;
        if (a->id == p->id){
            next_iteration(&pos, &a_slot);
            continue;
        }
        if (a->state == EGG){
            little_operation(&a, p, my_t, pos);
            some_operation(&pos, &a_slot, my_t, p);
            continue;
        }
        my_t->world_map[p->x][p->y].num_of_player--;
        delete_without_free_from_list(pos, LIST_OF_PLAYER);
        ejection(p, my_t, a);
        pos++;
        a_slot = a_slot->next;
    }
}
