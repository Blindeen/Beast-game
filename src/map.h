#ifndef GAME_BEAST_MAP_H
#define GAME_BEAST_MAP_H

#include "player_t.h"

//Max map dimensions
#define MAX_MAP_HEIGHT 128
#define MAX_MAP_WIDTH 128

//Map dimensions
#define MAP_HEIGHT 27
#define MAP_WIDTH 53

//Colors definitions
#define WALL 1
#define PLAYER 2
#define MONEY 3
#define CAMPSITE 4
#define BEAST 5

//Campsite coords
#define CAMPSITE_X 23
#define CAMPSITE_Y 11

//Player view
#define P_HEIGHT 5
#define P_WIDTH 5

int map_load(char map[][MAX_MAP_WIDTH+1]); //Loads a map to static array
void map_print(char map[][MAX_MAP_WIDTH+1]); //Prints a map from static array
void print_player(struct point_t *coords, char num); //Prints player on console
void copy_map(char map[][MAX_MAP_WIDTH+1], struct player_t *player, char o_map[][P_WIDTH+1]); //Copies a part of the map
void print_player_map(char map[][P_WIDTH+1], struct point_t *coords); //Print a player's part of the map
int is_camp_in_range(char map[][P_WIDTH+1]);
void print_empty_fields();
void print_beast(struct point_t *coords);


#endif
