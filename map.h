#ifndef GAME_BEAST_MAP_H
#define GAME_BEAST_MAP_H

//Max map dimensions
#define MAX_MAP_HEIGHT 128
#define MAX_MAP_WIDTH 128

//Colors definitions
#define WALL 1
#define PLAYER 2
#define MONEY 3
#define CAMPSITE 4
#define BEAST 5

//Map treasures
#define COIN 1
#define TREASURE 10
#define LTREASURE 50

//Campsite coords
#define CAMPSITE_X 23
#define CAMPSITE_Y 11

//Map structure
struct map_t{
    char **map;
    int width;
    int height;
};

struct map_t *map_init(); //Initializes a map
int map_load(char map[][MAX_MAP_WIDTH+1]); //Loads a map to static array
void map_print(char map[][MAX_MAP_WIDTH+1]); //Prints a map from static array
void map_display(struct map_t *map); //Displays an entire map
void destroy_map_structure(struct map_t **map); //Destroys a map structure

#endif
