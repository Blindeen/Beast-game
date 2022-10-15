#include <stdlib.h>
#include <time.h>
#include "player.h"

int initialize_player(struct player_t *player)
{
    srand(time(NULL));

    if(player == NULL)
    {
        return 0;
    }

    player->pid = rand();
    player->type = "HUMAN";
    player->curr_cooridantes.x = rand()%52;
    player->curr_cooridantes.y = rand()%25;
    player->deaths = 0;
    player->current_balance = 0;
    player->total_balance = 0;

    return 1;
}

int spawn_player(struct player_t *player, char map[][129])
{
    if(player == NULL)
    {
        return 0;
    }

    int x = player->curr_cooridantes.x;
    int y = player->curr_cooridantes.y;

    map[y][x] = '1';

    return 1;

}
