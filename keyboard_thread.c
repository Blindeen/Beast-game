#include <ncurses.h>
#include "keyboard_thread.h"

void *recv_key(void *arg)
{
    int *key = (int *)arg;
    timeout(50);
    while(1)
    {
        *key = getch();
    }

    return NULL;
}