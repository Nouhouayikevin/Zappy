/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** generic_list
*/

#include "../include/my.h"
void free_gen_li(linked_list_t **list)
{
    linked_list_t *temp = NULL;

    while (*list != NULL){
        temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}
