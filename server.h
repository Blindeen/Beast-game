#ifndef GAME_BEAST_SERVER_H
#define GAME_BEAST_SERVER_H

#include <pthread.h>

//Coordinates structure
struct point_t{
    int x;
    int y;
};

//Player structure
struct player_t{
    int pid;
    int psocket;
    pthread_t pthread;
    char *type;
    struct point_t curr_cooridantes;
    struct point_t spawn_point;
    int deaths;
    int current_balance;
    int total_balance;
};

struct server_info{
    int server_socket;
    char map[128][129];
    int curr_connection;
    struct player_t players[4];
    unsigned long rounds;
};

struct data_modif{
    int connected_socket;
    char **map;
};

int initialize_player(struct player_t *player, char map[][129]); //Initializes player
void spawn_player(struct player_t *player, char map[][129]); //Sets player on a map
void move_player(struct player_t *player, char map[][129], char dir); //Moves player
void validate_field(struct player_t *player, char map[][129]); //Checks next field
void *server_accept(void *arg);
void *receive_data(void *arg);
void game_server_loop(int server_socket); //Server's loop

#endif
