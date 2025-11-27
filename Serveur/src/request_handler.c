/*
** EPITECH PROJECT, 2025
** network
** File description:
** network
*/

#include "../include/my.h"
#include "ctype.h"
int ligne(char *str)
{
    int i = 0;
    int j = 0;

    while (str[i] != '\0'){
        if (str[i] == ' ')
            j++;
        while (str[i] == ' ')
            i++;
        if (str[i] == '\0')
            break;
        i++;
    }
    return j;
}

char *str_to_upper(char *request)
{
    if (request == NULL)
        return NULL;
    for (int i = 0; request[i] != '\0'; i++){
        request[i] = toupper(request[i]);
    }
    return request;
}

char **split_request(char *request)
{
    char **map;
    char *token;
    int i = 0;

    for (int i = 0; request[i] != '\0'; i++)
        if (request[i] == '\n' || request[i] == '\r')
            request[i] = ' ';
    map = malloc(sizeof(char *) * (ligne(request) + 2));
    token = strtok(request, " ");
    if (token != NULL){
        while (token != NULL){
            map[i] = strdup(token);
            token = strtok(NULL, " \n");
            i++;
        }
        map[i] = NULL;
    } else
        map[0] = NULL;
    map[0] = str_to_upper(map[0]);
    return map;
}

void accept_connection(int total, int socketfd, struct sockaddr_in *address,
    struct pollfd *handler)
{
    int pos = 0;
    int new_socket = 0;
    socklen_t len = sizeof(*address);

    printf("in accept\n");
    new_socket = accept(socketfd, (struct sockaddr*)address, &len);
    if (new_socket < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    write(new_socket, "WELCOME\n", 8);
    for (pos = 1; handler[pos].fd != -1 && pos < total; pos++);
    if (pos < total){
        handler[pos].fd = new_socket;
        handler[pos].events = POLLIN | POLLHUP | POLLERR;
    }
}

void wait_event(network_t *my_t, linked_list_t *team, params_t my_params)
{
    for (int i = 0; i < my_t->total_fd; i++){
        if (my_t->handler[i].fd == -1)
            continue;
        if ((my_t->handler[i].revents & POLLHUP || my_t->handler[i].revents
            & POLLERR)){
            close(my_t->handler[i].fd);
            my_t->handler[i].fd = -1;
            my_t->handler[i].events = 0;
            continue;
        }
        if (i == 0 && my_t->handler[0].revents & POLLIN){
            accept_connection(my_t->total_fd, my_t->sfd, &my_t->address,
                my_t->handler);
            continue;
        }
        if (i != 0 && my_t->handler[i].revents & POLLIN)
                command_handler(my_t, i, team, my_params);
    }
    exec_last_instruction(my_t, team);
    handle_death(team, my_t);
}
