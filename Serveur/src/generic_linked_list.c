/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** generic_linked_list
*/

#include "../include/my.h"

void push_in_list(void *data, linked_list_t **old)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));

    new->data = data;
    new->type = 0;
    new->next = *old;
    *old = new;
}

int list_length(linked_list_t *list)
{
    linked_list_t *temp = list;
    int count = 0;

    if (list == NULL)
        return 0;
    while (temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

bool delete_from_list(int pos, linked_list_t **list)
{
    int i = 0;
    linked_list_t *temp = *list;
    linked_list_t *prev = *list;
    linked_list_t *free_this = NULL;

    if (*list == NULL)
        return false;
    while (i < pos && temp != NULL){
        if (i < pos)
            prev = temp;
        temp = temp->next;
        i++;
        if (i <= pos && temp == NULL)
            return false;
    }
    free_this = temp;
    if (pos == 0)
        *list = (*list)->next;
    free_each(pos, prev, temp, free_this);
    return true;
}

bool delete_without_free_from_list(int pos, linked_list_t **list)
{
    int i = 0;
    linked_list_t *temp = *list;
    linked_list_t *prev = *list;
    linked_list_t *free_this = NULL;

    if (*list == NULL)
        return false;
    while (i < pos && temp != NULL){
        if (i < pos)
            prev = temp;
        temp = temp->next;
        i++;
        if (i <= pos && temp == NULL)
            return false;
    }
    free_this = temp;
    if (pos == 0)
        *list = (*list)->next;
    return true;
}

void free_each(int pos, linked_list_t *prev, linked_list_t *temp,
    linked_list_t *free_this)
{
    prev->next = temp->next;
    if (free_this != NULL)
        free(free_this);
}
