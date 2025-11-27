/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** command_identifier
*/

#include "../include/my.h"

static int reft_of_cmd(char *str)
{
    if (!strcmp(str, "Look"))
        return LOOK;
    if (!strcmp(str, "Take"))
        return TAKE;
    if (!strcmp(str, "Set"))
        return SET;
    if (!strcmp(str, "Fork"))
        return FORK;
    if (!strcmp(str, "Eject"))
        return EJECT;
    if (!strcmp(str, "Incantation"))
        return INCANTATION_FUN;
    if (!strcmp(str, "Broadcast"))
        return BROADCAST;
    return -1;
}

int cmd_identifier(char *str)
{
    if (!strcmp(str, "Forward"))
        return FORWARD;
    if (!strcmp(str, "Right"))
        return RIGHT;
    if (!strcmp(str, "Left"))
        return LEFT;
    if (!strcmp(str, "Connect_nbr"))
        return CONNECT;
    if (!strcmp(str, "Inventory"))
        return INVENTORY;
    return reft_of_cmd(str);
}

int identifier_resources(char *str)
{
    if (!strcmp(str, "food"))
        return FOOD;
    if (!strcmp(str, "linemate"))
        return LINEMATE;
    if (!strcmp(str, "deraumere"))
        return DERAUMERE;
    if (!strcmp(str, "sibur"))
        return SIBUR;
    if (!strcmp(str, "mendiane"))
        return MENDIANE;
    if (!strcmp(str, "phiras"))
        return PHIRAS;
    if (!strcmp(str, "thystame"))
        return THYSTAME;
    return -1;
}

int cmd_delay_giver(int the_cmd)
{
    if (the_cmd == FORWARD || the_cmd == RIGHT || the_cmd == LEFT || the_cmd ==
    LOOK || the_cmd == BROADCAST || the_cmd == EJECT
    || the_cmd == SET || the_cmd == TAKE)
        return 7;
    if (the_cmd == INVENTORY)
        return 1;
    if (the_cmd == FORK)
        return 42;
    if (the_cmd == INCANTATION_FUN)
        return 30;
    return -1;
}
