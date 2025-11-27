/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** params_parser
*/
#include "../include/my.h"

params_t simple_error_case(params_t prog_params, char **av, int ac, int *c)
{
    if (ac < 9){
        show_my_usage();
        exit(84);
    }
    if (!two_params_checker("-p", av, 2))
        exit(84);
    prog_params.port = atoi(av[2]);
    if (!two_params_checker("-x", av, 4))
        exit(84);
    prog_params.width = atoi(av[4]);
    if (!two_params_checker("-y", av, 6) || strcmp(av[7], "-n") != 0)
        exit(84);
    prog_params.heigth = atoi(av[6]);
    *c = check_c_and_f(av);
    if (c == 0 || !is_string_digit(av[*c + 1]))
        exit(84);
    prog_params.client_num = atoi(av[*c + 1]);
    prog_params.user_name = malloc(sizeof(char *) *
    (*c - 7));
    return prog_params;
}

params_t params_getter(char **av, int ac)
{
    params_t prog_params;
    int c = 0;
    int i = 0;

    call_signal();
    prog_params = simple_error_case(prog_params, av, ac, &c);
    for (i = 8; av[i] != NULL && strcmp(av[i], "-c") != 0; i++){
        prog_params.user_name[i - 8] = strdup(av[i]);
    }
    prog_params.user_name[i - 8] = NULL;
    if (ac < c + 3)
        return prog_params;
    if (!two_params_checker("-f", av, c + 3))
        exit(84);
    prog_params.freq = atoi(av[c + 3]);
    if (prog_params.width == 0 || prog_params.heigth == 0)
        exit(84);
    return prog_params;
}

void free_params(params_t my_params)
{
    for (int i = 0; my_params.user_name[i] != NULL; i++)
        free(my_params.user_name[i]);
    free(my_params.user_name);
}

void print_params(params_t paramet)
{
    printf("port : %d\n", paramet.port);
    printf("width : %d\n", paramet.width);
    printf("heigth : %d\n", paramet.heigth);
    printf("name");
    for (int i = 0; paramet.user_name[i] != NULL; i++){
        printf("-%s\n", paramet.user_name[i]);
    }
    printf("nomber of player : %d\n", paramet.client_num);
    printf("frequence : %d\n", paramet.freq);
}
