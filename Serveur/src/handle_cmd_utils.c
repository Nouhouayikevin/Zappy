/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** handle_cmd_utils
*/
#include "../include/my.h"
//This function will give you the last cmd the one you have to exec
cmd_t *give_me_the_last_cmd(linked_list_t *cmd)
{
    cmd_t *last_one = NULL;
    cmd_t *chosen_one = NULL;
    int count = 0;

    for (linked_list_t *temp = cmd; temp != NULL; temp = temp->next){
        last_one = (cmd_t *)temp->data;
        if (last_one->player->state == INACTIVE || last_one->cmd == -1 ||
        (last_one->player->state == INCANTATION && last_one->cmd !=
            INCANTATION_FUN)){
            count++;
            continue;
        }
        if (does_exceed(last_one)){
            chosen_one = (cmd_t *)temp->data;
            chosen_one->count = count;
            count++;
        }
    }
    return chosen_one;
}

bool does_exceed(cmd_t *last_one)
{
    printf("the cmd = %s\n", last_one->tab[0]);
    printf("time right now = %.2f\n", difftime(time(NULL), last_one->when));
    printf("time it should be = %.2f\n", last_one->delay /
    (double)last_one->my_programs_f);
    if (last_one->delay < 0)
        return true;
    if (difftime(time(NULL), last_one->when)
    >= last_one->delay / (double)last_one->my_programs_f){
        return true;
    } else
        return false;
}

int give_me_the_last_pos(linked_list_t *cmd)
{
    cmd_t *last_one = NULL;
    int count = 0;

    for (linked_list_t *temp = cmd; temp != NULL; temp = temp->next){
        last_one = (cmd_t *)temp->data;
        if (last_one->player->state == INACTIVE){
            count++;
            continue;
        }
        if (last_one->player->state == INCANTATION &&
            last_one->cmd != INCANTATION_FUN){
            count++;
            continue;
        }
        if (does_exceed(last_one))
            count++;
    }
    return count;
}
