#include "beast_thread.h"
#include "beast_t.h"
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t mut;

void *beast_thread(void *arg)
{
    struct server_info *info = (struct server_info *)arg;

    struct beast_t *beast = find_beast_spot(info);
    if(!beast)
    {
        return NULL;
    }

    beast->curr_cooridantes = find_empty_field(info->map);

    srand(time(NULL));
    while(info->game_status)
    {
        pthread_mutex_lock(&mut);
        beast->direction = rand()%4;
        pthread_mutex_unlock(&mut);
    }

    return NULL;
}