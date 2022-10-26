#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "server.h"
#include "UI.h"
#include "map.h"
#include "keyboard_thread.h"
#include <sys/socket.h>
#include <string.h>

struct player_t *find_players_spot(struct server_info *info)
{
    if(info)
    {
        for(int i = 0; i < 4; ++i)
        {
            if(!info->players[i].pid)
            {
                info->players[i].num = i+1+'0';
                return &info->players[i];
            }
        }
    }

    return NULL;
}

int initialize_player(struct player_t *player, char map[][129])
{
    srand(time(NULL));

    if(player == NULL)
    {
        return 0;
    }

    struct point_t empty_field = find_empty_field(map);

    player->spawn_point = empty_field;
    player->curr_cooridantes = empty_field;
    player->deaths = 0;
    player->current_balance = 0;
    player->total_balance = 0;

    return 1;
}

struct point_t find_empty_field(char map[][129])
{
    int x, y;
    do {
        x = rand()%52;
        y = rand()%25;
    }while(map[y][x] != ' ');

    return (struct point_t){x, y};
}

void move_player(struct player_t *player, char map[][129])
{
    if(player)
    {
        int x = player->curr_cooridantes.x, y = player->curr_cooridantes.y;

        switch (player->key) {
            case KEY_UP:
            {
                if(map[y-1][x] != 'W')
                {
                    y -= 1;
                    player->curr_cooridantes.y = y;
                }
            }
                break;
            case KEY_LEFT:
            {
                if(map[y][x-1] != 'W')
                {
                    x -= 1;
                    player->curr_cooridantes.x = x;
                }
            }
                break;
            case KEY_RIGHT:
            {
                if(map[y][x+1] != 'W')
                {
                    x += 1;
                    player->curr_cooridantes.x = x;
                }
            }
                break;
            case KEY_DOWN:
            {
                if(map[y+1][x] != 'W')
                {
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
    struct server_info *client_data = (struct server_info *)arg;

    int new_socket;
    while(client_data->game_status)
    {
        if ((new_socket = accept(client_data->server_socket, NULL, NULL)) < 0)
        {
            continue;
        }
        struct player_t *new_player = find_players_spot(client_data);
        if(new_player == NULL)
        {
            close(new_socket);
            continue;

        }
        new_player->psocket = new_socket;

        initialize_player(new_player, client_data->map);
        client_data->players_number++;

        struct recv_data_arguments *a = (struct recv_data_arguments *) malloc(sizeof(struct recv_data_arguments));
        a->info = client_data;
        a->player = new_player;
        pthread_create(&new_player->pthread, NULL, receive_data, (void *)a);
    }

    return NULL;
}

void *receive_data(void *arg)
{
    struct recv_data_arguments client_data = *(struct recv_data_arguments *)arg;
    free(arg);
    struct player_packet recv_packet;

    while(client_data.info->game_status)
    {
        if(recv(client_data.player->psocket, &recv_packet, sizeof(struct player_packet), 0) <= 0)
        {
            close(client_data.player->psocket);
            memset(client_data.player, 0, sizeof(struct player_t));
            client_data.info->players_number--;
            return NULL;
        }
        else
        {
            client_data.player->pid = recv_packet.pid;
            if(recv_packet.key == 'q')
            {
                close(client_data.player->psocket);
                memset(client_data.player, 0, sizeof(struct player_t));
                client_data.info->players_number--;
                return NULL;
            }
            if(recv_packet.key != -1)
            {
                client_data.player->key = recv_packet.key;
                client_data.player->key_flag = 1;
            }
        }
    }

    return NULL;
}

void game_server_loop(int server_socket)
{
    initscr();
    curs_set(0);
    noecho();
    start_color();

    struct server_info info;
    memset(info.players, 0, 4* sizeof(struct player_t));

    map_load(info.map);

    info.server_socket = server_socket;
    info.rounds = 0;
    info.game_status = 1;
    info.players_number = 0;

    pthread_t thread_accept;
    pthread_create(&thread_accept, NULL, server_accept, &info);
    pthread_detach(thread_accept);

//    int key;
//    pthread_t key_thread;
//    pthread_create(&key_thread, NULL, recv_key, &key);

    while(info.game_status)
    {
//        if(key == 'q')
//        {
//            info.game_status = 0;
//        }
        map_print(info.map);
        //display_ui(&info.players[0], info.rounds);
        for(int i = 0; i < 4; ++i)
        {
            if(info.players[i].pid && info.players[i].key_flag)
            {
                move_player(&info.players[i], info.map);
                info.players[i].key_flag = 0;
            }

        }
        for(int i=0; i < 4; ++i)
        {
            if(info.players[i].pid)
            {
                    print_player(&info.players[i]);
//                struct clients_data data;
//
//                data.current_balance = 0;
//                data.total_balance = 0;
//                data.deaths = 0;
//                data.position = info.players[0].curr_cooridantes;
//                data.server_id = 20;
//                data.game_status = 1;

//                send(info.players[i].psocket, &data, sizeof(struct clients_data), 0);
            }
        }
        usleep(500000);
//        key = -1;
    }

    pthread_cancel(thread_accept);

    endwin();
}