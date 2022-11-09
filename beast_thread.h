#ifndef GAME_BEAST_BEAST_THREAD_H
#define GAME_BEAST_BEAST_THREAD_H

#include "server.h"
#include <pthread.h>

struct beast_t_thread{
    struct server_info *info;
    struct beast_t *beast;
};

enum directions{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void *beast_thread(void *arg);
struct point_t* player_in_beast_range(struct beast_t *beast, struct server_info *info);

pthread_mutex_t mutex;

#endif
