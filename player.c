#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "player.h"
#include "map.h"

int initialize_player(struct player_t *player, char map[][129])
{
    srand(time(NULL));

    if(player == NULL)
    {
        return 0;
    }

    int x, y;
    do {
        x = rand()%52;
        y = rand()%25;
    }while(map[y][x] != ' ');

    player->pid = rand();
    player->type = "HUMAN";
    player->curr_cooridantes.x = x;
    player->curr_cooridantes.y = y;
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

int move_player(struct player_t *player, char map[][129])
{
    if(player == NULL)
    {
        return 0;
    }

    int x = player->curr_cooridantes.x, y = player->curr_cooridantes.y;

    keypad(stdscr, TRUE);

    switch (getch()) {
        case KEY_UP:
        {
            if(map[y-1][x] != 'W')
            {
                if(x == X && y == Y)
                {
                    map[y][x] = 'A';
                }
                else
                {
                    map[y][x] = ' ';
                }
                y -= 1;
                player->curr_cooridantes.y = y;
            }
        }
            break;
        case KEY_LEFT:
        {
            if(map[y][x-1] != 'W')
            {
                if(x == X && y == Y)
                {
                    map[y][x] = 'A';
                }
                else
                {
                    map[y][x] = ' ';
                }
                x -= 1;
                player->curr_cooridantes.x = x;
            }
        }
            break;
        case KEY_RIGHT:
        {
            if(map[y][x+1] != 'W')
            {
                if(x == X && y == Y)
                {
                    map[y][x] = 'A';
                }
                else
                {
                    map[y][x] = ' ';
                }
                x += 1;
                player->curr_cooridantes.x = x;
            }
        }
            break;
        case KEY_DOWN:
        {
            if(map[y+1][x] != 'W')
            {
                if(x == X && y == Y)
                {
                    map[y][x] = 'A';
                }
                else
                {
                    map[y][x] = ' ';
                }
                y += 1;
                player->curr_cooridantes.y = y;
            }
        }
            break;
        default:
        {

        }
    }

    validate_field(player, map);
    map[y][x] = '1';

    return 1;
}

void validate_field(struct player_t *player, char map[][129])
{
    if(player)
    {
        int x = player->curr_cooridantes.x, y = player->curr_cooridantes.y;

        switch (map[y][x]) {
            case 'c':
            {
                player->current_balance += 1;
            }
                break;
            case 'C':
            {
                player->current_balance += 10;
            }
                break;
            case 'T':
            {
                player->current_balance += 50;
            }
                break;
            case 'A':
            {
                player->total_balance += player->current_balance;
                player->current_balance = 0;
            }
                break;
            default:{

            }
        }
    }
}
