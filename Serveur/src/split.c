/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** split
*/

#include "../include/my.h"

char **split(char *str)
{
    char *temp = strdup(str);
    char **cmd = malloc(sizeof(char *) * 3);
    char *result = strtok(str, " ");
    int pos = 0;

    printf("result = %s\n", result);
    if (result == NULL)
        return NULL;
    while (result != NULL){
        cmd[pos] = strdup(result);
        result = strtok(NULL, " ");
        pos++;
    }
    cmd[pos] = NULL;
    return cmd;
}
