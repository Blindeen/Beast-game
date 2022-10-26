#ifndef GAME_BEAST_SERVER_H
#define GAME_BEAST_SERVER_H

#include <pthread.h>
#include "point.h"
#include "dt_structures.h"
#include "player_t.h"

//Game server info
struct server_info{
    int server_socket;
    unsigned int game_status:1;

    char map[128][129];
    struct player_t players[4];
    unsigned int players_number;
    unsigned long rounds;
};

struct recv_data_arguments{
    struct player_t *player;
    struct server_info *info;
};

struct player_t *find_players_spot(struct server_info *info);
int initialize_player(struct player_t *player, char map[][129]); //Initializes player
struct point_t find_empty_field(char map[][129]);
void move_player(struct player_t *player, char map[][129]); //Moves player
void validate_field(struct player_t *player, char map[][129]); //Checks next field
void *server_accept(void *arg);
void *receive_data(void *arg);
void game_server_loop(int server_socket); //Server's loop

#endif
