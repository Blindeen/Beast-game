#ifndef GAME_BEAST_SERVER_H
#define GAME_BEAST_SERVER_H

#include <pthread.h>
#include "point.h"
#include "dt_structures.h"
#include "player_t.h"
#include "map.h"
#include "doubly_linked_list.h"
#include "doubly_linked_list_beast.h"

//Map treasures
#define COIN 1
#define TREASURE 10
#define LTREASURE 50

//Game server info
struct server_info{
    int server_socket;
    unsigned int game_status:1;

    char map[128][129];
    struct player_t players[4];
    unsigned int players_number;
    unsigned long rounds;

    struct doubly_linked_list_t *dropped_treasures;
    struct doubly_linked_list_beast_t *beasts;
};

struct recv_data_arguments{
    struct player_t *player;
    struct server_info *info;
};

void players_in_range(struct point_t *players_pos, struct player_t *player, struct player_t *players);
void put_coins(char map[][MAX_MAP_WIDTH+1], int* key);
int is_colision(struct player_t *player, struct server_info *info); //Checks if collision has happened
struct player_t *find_players_spot(struct server_info *info); //Finds empty position in player_t array
int initialize_player(struct player_t *player, char map[][MAX_MAP_WIDTH+1]); //Initializes player
struct point_t find_empty_field(char map[][MAX_MAP_WIDTH+1]); //Finds empty field on the map
void move_player(struct player_t *player, struct server_info *info); //Moves player
void validate_field(struct player_t *player, struct server_info *info); //Checks next field
void *server_accept(void *arg); //Accepts clients' connection (thread)
void *receive_data(void *arg); //Receives clients' data (thread)
void game_server_loop(int server_socket); //Server's loop

#endif
