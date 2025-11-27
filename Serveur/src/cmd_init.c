/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** cmd_init
*/

#include "../include/my.h"

void functions_init(network_t *my_t)
{
    my_t->last_respawn = time(NULL);
    my_t->graphics_id = NULL;
    my_t->queue = NULL;
    my_t->cmd[FORWARD] = forward;
    my_t->cmd[LEFT] = left;
    my_t->cmd[RIGHT] = right;
    my_t->cmd[CONNECT] = connect_nbr;
    my_t->cmd[INVENTORY] = check_inventory;
    my_t->cmd[LOOK] = look;
    my_t->cmd[TAKE] = take;
    my_t->cmd[SET] = set;
    my_t->cmd[EJECT] = eject;
    my_t->cmd[FORK] = fork_f;
    my_t->cmd[INCANTATION_FUN] = exec_incantation;
    my_t->cmd[BROADCAST] = broadcast;
}
