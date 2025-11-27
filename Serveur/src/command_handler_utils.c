/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** command_handler_utils
*/

#include "../include/my.h"

void send_world_size(network_t *my_t, int id, params_t my_params)
{
    char *send_message = int_to_str(my_params.width);
    char *second_message = int_to_str(my_params.heigth);
    int tot_size = strlen(send_message) + strlen(second_message);
    char the_total_message[tot_size + 3];

    the_total_message[0] = '\0';
    strcat(the_total_message, send_message);
    strcat(the_total_message, " ");
    strcat(the_total_message, second_message);
    strcat(the_total_message, "\n");
    write(my_t->handler[id].fd, the_total_message, strlen(the_total_message));
    free(send_message);
    free(second_message);
}

void send_connect_nbr(linked_list_t *team, int id, char *temp, network_t *my_t)
{
    char *send_message = int_to_str(available_slot(id, team, my_t) + 1);
    char big_array[strlen(send_message) + 1];

    big_array[0] = '\0';
    strcpy(big_array, send_message);
    big_array[strlen(send_message)] = '\n';
    big_array[strlen(send_message) + 1] = '\0';
    write(my_t->handler[id].fd, big_array, strlen(send_message) + 1);
    free(send_message);
}

void new_cmd_init(cmd_t **new_cmd, network_t *my_t)
{
    time(&(*new_cmd)->when);
    (*new_cmd)->player->count++;
    (*new_cmd)->delay = cmd_delay_giver((*new_cmd)->cmd);
    (*new_cmd)->my_programs_f = my_t->my_params.freq;
    printf("before list_size = %d\n", list_length(my_t->queue));
    push_in_list((*new_cmd), &my_t->queue);
    printf("after list_size = %d\n", list_length(my_t->queue));
}

void exec_instruction_part(linked_list_t *team, int id, char *temp,
    network_t *my_t)
{
    cmd_t *new_cmd = malloc(sizeof(cmd_t));
    char **split_cmd = split(strdup(temp));

    new_cmd->request = strdup(temp);
    new_cmd->tab = split_cmd;
    new_cmd->player = get_player_slot(team, id);
    if (split_cmd == NULL){
        free(new_cmd);
        return;
    }
    new_cmd->cmd = cmd_identifier(split_cmd[0]);
    if (new_cmd->cmd == INCANTATION_FUN)
        new_cmd->cmd = incantation(id, team, my_t);
    if (new_cmd->cmd < 0 || new_cmd->player->count == 10){
        if (new_cmd->cmd == -1)
            write(my_t->handler[id].fd, "ko\n", 3);
        free(new_cmd);
        return;
    }
    new_cmd_init(&new_cmd, my_t);
}
