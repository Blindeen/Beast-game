#include <ncurses.h>
#include "keyboard_thread.h"
#include "server.h"

void *recv_key(void *arg)
{
    struct server_info *info = (struct server_info*)arg;
//    timeout(50);
    while(info->game_status)
    {
        info->key = getchar();
    }

    return NULL;
}