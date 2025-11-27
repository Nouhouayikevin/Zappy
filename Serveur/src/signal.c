/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** signal
*/
#include "../include/my.h"

void call_signal(void)
{
    signal(SIGINT, myhandler);
    signal(SIGSEGV, myhandler);
}

void myhandler(int signum)
{
    if (signum == SIGSEGV) {
        printf("Caught signal  %d exiting gracefully...\n", signum);
        exit(84);
    }
    if (signum == SIGINT) {
        printf("Interrupting the program...\n");
        for (int x = memory->my_params.heigth - 1; x > 0; x--)
                free(memory->world_map[x]);
        exit(0);
    }
}
