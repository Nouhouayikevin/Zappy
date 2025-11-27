/*
** EPITECH PROJECT, 2024
** risjf
** File description:
** s,kfk
*/

#ifndef _NET_WORK_
    #define _NET_WORK_
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <stdio.h>
    #include <errno.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <string.h>
    #include <stdlib.h>
    #include <poll.h>
    #include <dirent.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <time.h>
    #include <arpa/inet.h>
    #include <ctype.h>
    #include <math.h>
    #include <stdbool.h>
    #define PORT (atoi(av[2]))
    #define BACKLOG 110
    #define B_SIZE 1024
    #define H_SIZE 100
    #define DEFAULT_FREQ 100
    #define LIMIT_INT_SIZE 10
    #define WL my_t->world_map[x][y].list_of_player
    #define LIST_OF_PLAYER &my_t->world_map[p->x][p->y].list_of_player
    #define WR w->resources
    #define AR a_player->resources
    #define MI my_t->i
    #define MJ my_t->j
    #define GID my_t->handler[id].fd
    #define PR p->resources
    #define WMP worldmap[player->x][player->y].list_of_player
    #define RI my_t->world_map[x][y].resources
    #define GRAPHIC send_sst(temp, id, my_t)
typedef struct sockaddr_in addr_t;
// int gen_count;
//This is for the different type of resources
enum RESOURCES {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

//A player could have three states either egg or DEAD or ALIVE
enum STATES {
    EGG,
    ALIVE,
    DEAD,
    INCANTATION,
    INACTIVE
};

// This enum is for the differents types of command of an AICLIENT
enum AICLIENT {
    FORWARD,
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    CONNECT,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION_FUN
};

//This is for player direction
enum DIRECTION {
    NORTH,
    EAST,
    SOUTH,
    WEST
};


//This structure is to get the different parameter of the program
typedef struct params {
    int port;
    int width;
    int heigth;
    char **user_name;
    int client_num;
    int freq;
}params_t;

//This is my generic linked list
typedef struct linked_list {
    void *data;
    int type;
    struct linked_list *next;
}linked_list_t;
//This structure represent a simple tile
typedef struct tile {
    int x;
    int y;
    size_t resources[7];
    linked_list_t *list_of_player;
    int num_of_player;
}tile_t;

//This structure is for each team
typedef struct team_s {
    char *team_name;
    linked_list_t *slots;
    int total_slot;
    int available_slot;
}team_t;


//One player
typedef struct slot {
    int id;
    int state;
    int level;
    int x;
    int y;
    size_t resources[7];
    time_t since_last;
    int dir;
    int pos;
    int count;
    int index;
}slot_t;

// Resources generator structure
typedef struct share {
    linked_list_t *new;
    double food[6];
    double resources;
    double tot;
    double sum_up;
    int x0;
    linked_list_t *it;
    int y0;
    int incr;
    double r;
} share_t;

//pos structure
typedef struct pos {
    int x;
    int y;
}pos_t;

// This is my network basic structure
typedef struct network {
    int sfd;
    char *buffer;
    struct sockaddr_in address;
    struct pollfd *handler;
    char *request;
    int c;
    int nb;
    int listen;
    int the_size;
    char *msg;
    int total_fd;
    tile_t **world_map;
    params_t my_params;
    int command;
    linked_list_t *queue;
    void (*cmd[12])(int, linked_list_t *, struct network *my_t);
    char **request_tab;
    int count;
    int count_size;
    int level;
    int dir;
    int start;
    int end;
    time_t last_respawn;
    linked_list_t *graphics_id;
    linked_list_t *teams;
    int id;
    int *pos;
    int i;
    int j;
    tile_t *w;
}network_t;
extern network_t *memory;
//this function is for where the cmd function
typedef struct cmd {
    slot_t *player;
    int cmd;
    time_t when;
    int delay;
    int my_programs_f;
    char **tab;
    char *request;
    int count;
}cmd_t;
void send_sgt_to_graphics(int sender_id,
    network_t *my_t, char *value);
void send_bct_to_graphics(network_t *my_t, int x, int y);
void send_pin_to_graphics(int id,
    network_t *my_t, slot_t *p);
void call_signal(void);
void myhandler(int signum);
void broadcast(int id, linked_list_t *teams, network_t *my_t);
void checker(network_t *my_t, int x, int y, char *look_available);
void exec_incantation(int id, linked_list_t *teams, network_t *my_t);
int incantation(int id, linked_list_t *teams, network_t *my_t);
void forward_action(slot_t *player, network_t *my_t);
void right_action(slot_t *player);
void left_action(slot_t *player);
void egg_deleter(linked_list_t *teams, slot_t *a, slot_t *p, network_t *my_t);
bool eject_loop(slot_t *a, slot_t *p, network_t *my_t, linked_list_t *teams);
void msg_sender(network_t *my_t, slot_t *a, int value);
int add_new_player(linked_list_t *team, int id, char *the_team,
    network_t *my_t);
team_t *get_player_team_spec(linked_list_t *teams, int id, int x, int y);
bool check_user_in_team_spec(linked_list_t *slots, int id, int x, int y);
int total_alive_func(linked_list_t *players);
void nouth_ejection(slot_t *p, network_t *my_t, slot_t *a);
void south_ejection(slot_t *p, network_t *my_t, slot_t *a);
void east_ejection(slot_t *p, network_t *my_t, slot_t *a);
void west_ejection(slot_t *p, network_t *my_t, slot_t *a);
void fork_f(int id, linked_list_t *teams, network_t *my_t);
void eject(int id, linked_list_t *teams, network_t *my_t);
void resources_ew_inner_loop(char *look_available, network_t *my_t,
    int x, int y);
void resources_inner_loop(int temp, int i, char *look_available);
void new_cmd_init(cmd_t **new_cmd, network_t *my_t);
void handle_death_inner_condition(linked_list_t *teams, slot_t *player,
    network_t *my_t, team_t *a_team);
void inner_add_player_loop(linked_list_t **a_slot, team_t *a_team);
void handle_death(linked_list_t *teams, network_t *my_t);
void void_disconnect_action(network_t *my_t, int id,
    linked_list_t *team, params_t my_params);
void east_westen(network_t *my_t, char *look_available, slot_t *p);
void resources_ew(network_t *my_t, char *look_available, int y, slot_t *p);
void resources_sh(network_t *my_t, char *look_available, int x, slot_t *p);
void northen_southen(network_t *my_t, char *look_available, slot_t *p);
void resource_writer(int i, char *look_available);
void take(int id, linked_list_t *teams, network_t *my_t);
void set(int id, linked_list_t *team, network_t *my_t);
void look(int id, linked_list_t *team, network_t *my_t);
int identifier_resources(char *str);
void check_inventory(int id, linked_list_t *teams, network_t *my_t);
void check_inventory(int id, linked_list_t *teams, network_t *my_t);
int available_slot(int id, linked_list_t *teams, network_t *my_t);
void send_world_size(network_t *my_t, int id, params_t my_params);
void send_connect_nbr(linked_list_t *team, int id, char *temp,
    network_t *my_t);
void connect_sender(int total_active, network_t *my_t, int id);
void exec_instruction_part(linked_list_t *team, int id, char *temp,
    network_t *my_t);
void free_gen_li(linked_list_t **list);
void free_world(int x, int y, tile_t **world_map);
void init_network_t(params_t my_params, network_t *my_t, char **av,
    tile_t **worldmap);
team_t *get_player_team(linked_list_t *teams, int id);
int find_player_pos_in_the_slots(network_t *my_t, int id, linked_list_t *slot);
int find_player_pos_int_world(network_t *my_t, slot_t *player);
void exec_last_instruction(network_t *my_t, linked_list_t *teams);
slot_t *check_user_in_slot(linked_list_t *slots, int id);
bool check_user_in_team(linked_list_t *slots, int id);
bool does_exceed(cmd_t *last_one);
int give_me_the_last_pos(linked_list_t *cmd);
cmd_t *give_me_the_last_cmd(linked_list_t *cmd);
int cmd_delay_giver(int the_cmd);
void functions_init(network_t *my_t);
int cmd_identifier(char *str);
char **split(char *str);
int cmd_identifier(char *str);
void right(int id, linked_list_t *teams, network_t *my_t);
void left(int id, linked_list_t *teams, network_t *my_t);
void connect_nbr(int id, linked_list_t *teams, network_t *my_t);
void forward(int id, linked_list_t *teams, network_t *my_t);
void move(slot_t *player, network_t *my_t, int command);
bool delete_without_free_from_list(int pos, linked_list_t **list);
slot_t *get_player_slot(linked_list_t *teams, int id);
int add_player(linked_list_t *team, int id, char *the_team, network_t *my_t);
linked_list_t *create_team(params_t my_params, tile_t **worldmap);
void free_each(int pos, linked_list_t *prev, linked_list_t *temp,
    linked_list_t *free_this);
void free_world(int x, int y, tile_t **world_map);
void share_resource(share_t var, tile_t **world_map, int x, int y);
void free_params(params_t my_params);
int list_length(linked_list_t *list);
void push_in_list(void *data, linked_list_t **old);
double random_num(int min, int max);
bool delete_from_list(int pos, linked_list_t **list);
char *str_to_upper(char *request);
struct sockaddr_in init_socker(network_t my_t, char **av);
void init_binding(int socketfd, addr_t address, network_t *my_t, char **av);
void accept_connection(int count, int socketfd, struct sockaddr_in *address,
    struct pollfd *handler);
char **split_request(char *request);
int is_string_digit(char *s);
int two_params_checker(char *s, char **av, int pos);
int check_c_and_f(char **av);
params_t params_getter(char **av, int ac);
void print_params(params_t paramet);
tile_t **empty_world(int x, int y);
void share_foods(int x, int y, tile_t **world_map, share_t var);
void print_map(tile_t **world_map, int X, int Y);
void resource_array(int x, int y, tile_t **world_map, network_t *my_t);
char *int_to_str(int num);
void command_handler(network_t *my_t, int id, linked_list_t *team,
    params_t my_params);
void wait_event(network_t *my_t, linked_list_t *team, params_t my_params);
void exec_last_instruction(network_t *my_t, linked_list_t *teams);
void show_my_usage(void);
void send_sgt_to_graphic(network_t *my_t);
#endif
