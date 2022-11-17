#ifndef GAME_BEAST_BEAST_T_H
#define GAME_BEAST_BEAST_T_H

#include <pthread.h>
#include "point.h"

struct beast_t{
    pthread_mutex_t beast_mutex;
    struct point_t curr_cooridantes;
    unsigned int direction;
};

#endif
