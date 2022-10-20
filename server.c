#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "server.h"
#include "UI.h"
#include "map.h"
#include <pthread.h>
#include <sys/socket.h>

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
    player->spawn_point.x = x;
    player->spawn_point.y = y;
    player->curr_cooridantes.x = x;
    player->curr_cooridantes.y = y;
    player->deaths = 0;
    player->current_balance = 0;
    player->total_balance = 0;

    spawn_player(player, map);

    return 1;
}

void spawn_player(struct player_t *player, char map[][129])
{
    if(player)
    {
        int x = player->spawn_point.x;
        int y = player->spawn_point.y;

        map[y][x] = '1';
    }
}

void move_player(struct player_t *player, char map[][129], char dir)
{
    if(player)
    {
        int x = player->curr_cooridantes.x, y = player->curr_cooridantes.y;

        switch (dir) {
            case 'w':
            {
                if(map[y-1][x] != 'W')
                {
                    if(x == CAMPSITE_X && y == CAMPSITE_Y)
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
            case 'a':
            {
                if(map[y][x-1] != 'W')
                {
                    if(x == CAMPSITE_X && y == CAMPSITE_Y)
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
            case 'd':
            {
                if(map[y][x+1] != 'W')
                {
                    if(x == CAMPSITE_X && y == CAMPSITE_Y)
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
            case 's':
            {
                if(map[y+1][x] != 'W')
                {
                    if(x == CAMPSITE_X && y == CAMPSITE_Y)
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
    }

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

void *server_accept(void *arg)
{
    struct server_info *arguments = (struct server_info *)arg;
    int new_socket;

    while(1)
    {
        pthread_t recv_direction;
        if ((new_socket = accept(arguments->server_socket, NULL, NULL)) < 0)
        {
            continue;
        }
        arguments->curr_connection = new_socket;
        pthread_create(&recv_direction, NULL, receive_data, (void *)arguments);
    }
}

void *receive_data(void *arg)
{
    struct server_info *info = (struct server_info *)arg;
    char c;
    while(1)
    {
        if(recv(info->curr_connection, &c, sizeof(c), 0) <= 0)
        {
            close(info->curr_connection);
            return NULL;
        }
        else
        {
            move_player(&info->players[0], info->map, c);
            info->rounds+=1;
        }
    }
}

void game_server_loop(int server_socket)
{
    initscr();
    curs_set(0);

    struct server_info info;
    struct player_t player1;

    map_load(info.map);
    initialize_player(&player1, info.map);

    info.server_socket = server_socket;
    info.players[0] = player1;
    info.rounds = 0;

    pthread_t thread_accept;
    pthread_create(&thread_accept, NULL, server_accept, &info);
    pthread_detach(thread_accept);

    while(1)
    {
        map_print(info.map);
        display_ui(&info.players[0], info.rounds);
        usleep(500000);
    }

    pthread_cancel(thread_accept);

    endwin();


}