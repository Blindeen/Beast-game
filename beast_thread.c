#include "beast_thread.h"
#include "beast_t.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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
        usleep(500000);
        pthread_mutex_lock(&mutex);

        struct point_t *player_coords;
        if((player_coords = player_in_beast_range(beast, info)))
        {

            int x_diff = beast->curr_cooridantes.x - player_coords->x;
            int y_diff = beast->curr_cooridantes.y - player_coords->y;

            if(x_diff < 0 && y_diff < 0)
            {
                if(info->map[beast->curr_cooridantes.y][beast->curr_cooridantes.x+1] != 'W')
                {
                    beast->direction = RIGHT;
                }
                else if(info->map[beast->curr_cooridantes.y+1][beast->curr_cooridantes.x] != 'W')
                {
                    beast->direction = DOWN;
                }
            }
            else if(x_diff > 0 && y_diff > 0)
            {
                if(info->map[beast->curr_cooridantes.y][beast->curr_cooridantes.x-1] != 'W')
                {
                    beast->direction = LEFT;
                }
                else if(info->map[beast->curr_cooridantes.y-1][beast->curr_cooridantes.x] != 'W')
                {
                    beast->direction = UP;
                }
            }
            else if(x_diff < 0 && y_diff > 0)
            {
                if(info->map[beast->curr_cooridantes.y][beast->curr_cooridantes.x+1] != 'W')
                {
                    beast->direction = RIGHT;
                }
                else if(info->map[beast->curr_cooridantes.y-1][beast->curr_cooridantes.x] != 'W')
                {
                    beast->direction = UP;
                }
            }
            else if(x_diff > 0 && y_diff < 0)
            {
                if(info->map[beast->curr_cooridantes.y][beast->curr_cooridantes.x-1] != 'W')
                {
                    beast->direction = LEFT;
                }
                else if(info->map[beast->curr_cooridantes.y+1][beast->curr_cooridantes.x] != 'W')
                {
                    beast->direction = DOWN;
                }
            }
            else if(x_diff == 0 && y_diff < 0)
            {
                if(info->map[beast->curr_cooridantes.y+1][beast->curr_cooridantes.x] != 'W')
                {
                    beast->direction = DOWN;
                }
            }
            else if(x_diff == 0 && y_diff > 0)
            {
                if(info->map[beast->curr_cooridantes.y-1][beast->curr_cooridantes.x] != 'W')
                {
                    beast->direction = UP;
                }
            }
            else if(x_diff < 0 && y_diff == 0)
            {
                if(info->map[beast->curr_cooridantes.y][beast->curr_cooridantes.x+1] != 'W')
                {
                    beast->direction = RIGHT;
                }
            }
            else if(x_diff > 0 && y_diff == 0)
            {
                if(info->map[beast->curr_cooridantes.y][beast->curr_cooridantes.x-1] != 'W')
                {
                    beast->direction = LEFT;
                }
            }
        }
        else
        {
            beast->direction = rand()%4;
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

struct point_t* player_in_beast_range(struct beast_t *beast, struct server_info *info)
{
//    pthread_mutex_lock(&mut);

    if(beast && info)
    {
        int x = beast->curr_cooridantes.x - 2;
        int y = beast->curr_cooridantes.y - 2;

        for(int i = y; i < y+5; ++i)
        {
            for(int j = x; j < x+5; ++j)
            {
                for(int k = 0; k < 4; ++k)
                {
                    if(info->players[k].curr_cooridantes.x == j && info->players[k].curr_cooridantes.y == i)
                    {
                        return &info->players[k].curr_cooridantes;
                    }
                }
            }
        }
    }

    return NULL;
}