/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** int_to_str
*/
#include "../include/my.h"
char *int_to_str(int num)
{
    int size = 0;
    int temp = num;
    char *string = NULL;

    while (temp > 0){
        temp = temp / 10;
        size++;
    }
    temp = num;
    string = malloc(sizeof(char) * (size + 2));
    string[size] = '\0';
    for (int i = size - 1; i >= 0; i--){
        string[i] = (num % 10) + 48;
        num = num / 10;
    }
    if (temp == 0){
        string[0] = '0';
        string[1] = '\0';
    }
    return string;
}
