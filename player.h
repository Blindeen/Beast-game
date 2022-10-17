#ifndef GAME_BEAST_PLAYER_H
#define GAME_BEAST_PLAYER_H

//Coordinates structure
struct point_t{
    int x;
    int y;
};

//Player structure
struct player_t{
    int pid;
    char *type;
    struct point_t curr_cooridantes;
    int deaths;
    int current_balance;
    int total_balance;
};

int initialize_player(struct player_t *player, char map[][129]); //Initializes player
int spawn_player(struct player_t *player, char map[][129]);
int move_player(struct player_t *player, char map[][129]);
void validate_field(struct player_t *player, char map[][129]);

#endif
