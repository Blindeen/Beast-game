#ifndef GAME_BEAST_BEAST_THREAD_H
#define GAME_BEAST_BEAST_THREAD_H

#include "server.h"

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

#endif
