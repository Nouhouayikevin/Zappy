/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** params_utils
*/

#include "../include/my.h"

int is_string_digit(char *s)
{
    for (int i = 0; s[i]; i++){
        if (!isdigit(s[i])){
            return 0;
        }
    }
    return 1;
}

int two_params_checker(char *s, char **av, int pos)
{
    if (strcmp(av[pos - 1], s) != 0 || !is_string_digit(av[pos]))
        return 0;
    return 1;
}

int check_c_and_f(char **av)
{
    int c = 0;

    for (int i = 0; av[i] != NULL; i++){
        if (strcmp(av[i], "-c") == 0)
            c = i;
    }
    return c;
}
