#ifndef GAME_BEAST_PLAYER_T_H
#define GAME_BEAST_PLAYER_T_H

#include <pthread.h>
#include "point.h"

//Player's structure
struct player_t{
    int pid;
    int psocket;
    pthread_t pthread;

    int key;
    unsigned int key_flag:1;

    char num;
    struct point_t spawn_point;
    struct point_t curr_cooridantes;

    unsigned int deaths;
    unsigned int current_balance;
    unsigned int total_balance;
};

#endif
