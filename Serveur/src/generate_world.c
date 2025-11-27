/*
** EPITECH PROJECT, 2025
** B-YEP-400-COT-4-1-zappy-julcinia.oke
** File description:
** generate_world
*/

#include "../include/my.h"
static int total_resources(tile_t **world_map, int x, int y)
{
    int tot = 0;

    for (int i = 0; i < 7; i++){
        tot += world_map[x][y].resources[i];
    }
    return tot;
}

tile_t **empty_world(int x, int y)
{
    tile_t **new_world = malloc(sizeof(tile_t *) * (x + 1));

    for (int i = 0; i < x; i++){
        new_world[i] = malloc(sizeof(tile_t) * y);
        for (int j = 0; j < y; j++){
            new_world[i][j].y = j;
            new_world[i][j].x = i;
            new_world[i][j].resources[FOOD] = 0;
            new_world[i][j].resources[MENDIANE] = 0;
            new_world[i][j].resources[THYSTAME] = 0;
            new_world[i][j].resources[SIBUR] = 0;
            new_world[i][j].resources[PHIRAS] = 0;
            new_world[i][j].resources[DERAUMERE] = 0;
            new_world[i][j].resources[LINEMATE] = 0;
            new_world[i][j].list_of_player = NULL;
            new_world[i][j].num_of_player = 0;
        }
    }
    new_world[x] = NULL;
    return new_world;
}

void share_foods(int x, int y, tile_t **world_map, share_t var)
{
    int food = round(0.5 * x * y);

    for (int i = 0; i < x; i++){
        for (int j = 0; world_map[j] != NULL; j++){
            world_map[i][j].resources[FOOD] +=
            (total_resources(world_map, i, j) < 4) ? 1 : 0;
            food += -1;
        }
        if (food <= 0)
            break;
        if (i >= x)
            i = 0;
    }
    share_resource(var, world_map, x, y);
}

share_t weight_list_loop(share_t var, int j)
{
    for (int i = 0; i < round(var.resources); i++){
        push_in_list(&var.food[j], &var.new);
        if (j == 3)
            var.new->type = MENDIANE;
        if (j == 2)
            var.new->type = SIBUR;
        if (j == 0)
            var.new->type = LINEMATE;
        if (j == 1)
            var.new->type = DERAUMERE;
        if (j == 4)
            var.new->type = PHIRAS;
        if (j == 5)
            var.new->type = THYSTAME;
    }
    return var;
}

void resource_array(int x, int y, tile_t **world_map, network_t *my_t)
{
    int dx = random_num(0, x - 1);
    share_t var = {NULL, {0.3, 0.15, 0.1, 0.1, 0.08, 0.05}, 0, 0, 0, dx,
    NULL, 0, 0, 0};
    int total_resources = 0;

    for (int j = 0; j < 6; j++){
        var.resources = x * y * var.food[j];
        var.tot += round(var.resources) * var.food[j];
        var = weight_list_loop(var, j);
    }
    share_foods(x, y, world_map, var);
    send_sgt_to_graphic(my_t);
    for (int i = 0; i < x - 1; i++)
        for (int j = 0; j < y - 1; j++)
            send_bct_to_graphics(my_t, i, j);
}

static void init_var_t(share_t *var)
{
    var->r = random_num(0, round(var->tot));
    var->sum_up = 0;
    var->incr = 0;
}

void share_resource(share_t var, tile_t **world_map, int x, int y)
{
    while (var.tot > 0 && var.new != NULL){
        init_var_t(&var);
        for (var.it = var.new; (var.it->next != NULL && var.sum_up < var.r);
        var.it = var.it->next){
            var.sum_up += *(double *)var.it->data;
            var.incr++;
        }
        if (total_resources(world_map, var.x0, var.y0) < 4)
            world_map[var.x0][var.y0].resources[var.it->type] += 1;
        var.y0 += 1;
        if (var.y0 >= y - 1){
            var.x0 += 1;
            var.y0 = 0;
        }
        if (world_map[var.x0] == NULL)
            var.x0 = 0;
        var.tot += (-1 * *(double *)var.it->data);
        delete_from_list(var.incr, &var.new);
    }
}
