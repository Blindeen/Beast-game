#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "server.h"
#include "UI.h"
#include "keyboard_thread.h"
#include "beast_thread.h"

pthread_mutex_t mutex;

void beasts_in_range(struct point_t *beasts_pos, struct player_t *player, struct beast_t *beasts)
{
    if(beasts_pos && player && beasts)
    {
        int x = player->curr_cooridantes.x - 2;
        int y = player->curr_cooridantes.y - 2;

        for(int i = y; i < y+5; ++i)
        {
            for(int j = x; j < x+5; ++j)
            {
                for(int k = 0; k < 20; ++k)
                {
                    if(i == beasts[k].curr_cooridantes.y && j == beasts[k].curr_cooridantes.x)
                    {
                        beasts_pos[k].y = i;
                        beasts_pos[k].x = j;
                    }
                }
            }
        }
    }
}

void move_beast(struct beast_t *beast, struct server_info *info)
{
    if(beast && info)
    {

        int x = beast->curr_cooridantes.x;
        int y = beast->curr_cooridantes.y;

        switch (beast->direction) {
            case UP:
            {
                if(info->map[y-1][x] != 'W')
                {
                    y -= 1;
                    beast->curr_cooridantes.y = y;
                }
            }
                break;
            case DOWN:
            {
                if(info->map[y+1][x] != 'W')
                {
                    y += 1;
                    beast->curr_cooridantes.y = y;
                }
            }
                break;
            case LEFT:
            {
                if(info->map[y][x-1] != 'W')
                {
                    x -= 1;
                    beast->curr_cooridantes.x = x;
                }
            }
                break;
            case RIGHT:
            {
                if(info->map[y][x+1] != 'W')
                {
                    x += 1;
                    beast->curr_cooridantes.x = x;
                }
            }
                break;
            default:
            {

            }
        }

    }
}

struct beast_t *find_beast_spot(struct server_info *info)
{
    if(info)
    {
        for(int i = 0; i < 20; ++i)
        {
            if(!info->beasts[i].curr_cooridantes.x && !info->beasts[i].curr_cooridantes.y)
            {
                return &info->beasts[i];
            }
        }
    }

    return NULL;
}

void players_in_range(struct point_t *players_pos, struct player_t *player, struct player_t *players)
{
    if(players_pos && player && players)
    {
        int x = player->curr_cooridantes.x - 2;
        int y = player->curr_cooridantes.y - 2;

        for(int i = y; i < y+5; ++i)
        {
            for(int j = x; j < x+5; ++j)
            {
                for(int k = 0; k < 4; ++k)
                {
                    if(i == players[k].curr_cooridantes.y && j == players[k].curr_cooridantes.x && player->num != players[k].num)
                    {
                        players_pos[k].y = i;
                        players_pos[k].x = j;
                    }
                }
            }
        }
    }
}

void put_coins(char map[][MAX_MAP_WIDTH+1], int* key)
{
    struct point_t empty_field = find_empty_field(map);

    switch (*key) {
        case 'c':
        {
            map[empty_field.y][empty_field.x] = 'c';
            
        }
            break;
        case 'C':
        {
            map[empty_field.y][empty_field.x] = 'C';
        }
            break;
        case 'T':
        {
            map[empty_field.y][empty_field.x] = 'T';
        }
            break;
        default:
        {

        }
    }

    *key = -1;
}

int is_colision(struct player_t *player, struct server_info *info)
{
    if(!player || !info)
    {
        return -1;
    }

    for(int i = 0; i < 4; ++i)
    {
        if(player->curr_cooridantes.x == info->players[i].curr_cooridantes.x && player->curr_cooridantes.y == info->players[i].curr_cooridantes.y && player->num != info->players[i].num)
        {
            unsigned int treasure = player->current_balance + info->players[i].current_balance;

            if(treasure > 0)
            {
                dll_push_back(info->dropped_treasures, treasure, &player->curr_cooridantes);
                info->map[player->curr_cooridantes.y][player->curr_cooridantes.x] = 'D';
                player->current_balance = 0;
                info->players[i].current_balance = 0;
            }

            player->curr_cooridantes = player->spawn_point;
            info->players[i].curr_cooridantes = info->players[i].spawn_point;

            return 1;
        }
    }

    return 0;

}

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

int initialize_player(struct player_t *player, char map[][MAX_MAP_WIDTH+1])
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

struct point_t find_empty_field(char map[][MAX_MAP_WIDTH+1])
{
    //TODO: Change this function due to spawning two or more player in the exact location
    int x, y;
    do {
        x = rand()%52;
        y = rand()%25;
    }while(map[y][x] != ' ');

    return (struct point_t){x, y};
}

void move_player(struct player_t *player, struct server_info *info)
{
    if(player)
    {
        int x = player->curr_cooridantes.x, y = player->curr_cooridantes.y;

        if(info->map[player->curr_cooridantes.y][player->curr_cooridantes.x] == '#')
        {
            if(!player->slow)
            {
                player->slow = 1;
                return;
            }
            else
            {
                player->slow = 0;
            }
        }

        switch (player->key) {
            case KEY_UP:
            {
                if(info->map[y-1][x] != 'W')
                {
                    y -= 1;
                    player->curr_cooridantes.y = y;
                }
            }
                break;
            case KEY_LEFT:
            {
                if(info->map[y][x-1] != 'W')
                {
                    x -= 1;
                    player->curr_cooridantes.x = x;
                }
            }
                break;
            case KEY_RIGHT:
            {
                if(info->map[y][x+1] != 'W')
                {
                    x += 1;
                    player->curr_cooridantes.x = x;
                }
            }
                break;
            case KEY_DOWN:
            {
                if(info->map[y+1][x] != 'W')
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

        validate_field(player, info);
    }

}

void validate_field(struct player_t *player, struct server_info *info)
{
    if(player)
    {
        int x = player->curr_cooridantes.x, y = player->curr_cooridantes.y;

        switch (info->map[y][x]) {
            case 'c':
            {
                player->current_balance += COIN;
                info->map[y][x] = ' ';
            }
                break;
            case 'C':
            {
                player->current_balance += TREASURE;
                info->map[y][x] = ' ';
            }
                break;
            case 'T':
            {
                player->current_balance += LTREASURE;
                info->map[y][x] = ' ';
            }
                break;
            case 'A':
            {
                player->total_balance += player->current_balance;
                player->current_balance = 0;
            }
                break;
            case 'D':
            {
                player->current_balance += dll_remove(info->dropped_treasures, &player->curr_cooridantes, NULL);
                info->map[y][x] = ' ';
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
    memset(info.players, 0, 4 * sizeof(struct player_t));
    memset(info.beasts, 0, 20 * sizeof(struct beast_t));

    map_load(info.map);

    info.server_socket = server_socket;
    info.rounds = 0;
    info.game_status = 1;
    info.players_number = 0;
    info.dropped_treasures = dll_create();

    pthread_t thread_accept;
    pthread_create(&thread_accept, NULL, server_accept, &info);
    pthread_detach(thread_accept);

    int key = -1;
    pthread_t key_thread;
    pthread_create(&key_thread, NULL, recv_key, &key);

    while(info.game_status)
    {
        usleep(500000);

        if(key == 'q' || key == 'Q')
        {
            info.game_status = 0;
        }
        else if(key == 'b' || key == 'B')
        {
            pthread_t beast_th;
            pthread_create(&beast_th, NULL, beast_thread , &info);
        }

        put_coins(info.map, &key);
        map_print(info.map);
        display_ui(&info);

        for(int i = 0; i < 20; ++i)
        {
            if(info.beasts[i].curr_cooridantes.x || info.beasts[i].curr_cooridantes.y)
            {
                print_beast(&info.beasts[i].curr_cooridantes);
            }
        }

        for(int i = 0; i < 4; ++i)
        {
            if(info.players[i].pid && info.players[i].key_flag)
            {
                move_player(&info.players[i], &info);
                is_colision(&info.players[i], &info);
                info.players[i].key_flag = 0;
            }

        }

        for(int i = 0; i < 20; ++i)
        {
            if(info.beasts[i].curr_cooridantes.x || info.beasts[i].curr_cooridantes.y)
            {
                pthread_mutex_lock(&mutex);
                move_beast(&info.beasts[i], &info);
                pthread_mutex_unlock(&mutex);
            }
        }

        for(int i=0; i < 4; ++i)
        {
            if(info.players[i].pid)
            {
                print_player(&info.players[i].curr_cooridantes, info.players[i].num);

                struct clients_data data;
                memset(&data, 0, sizeof(struct clients_data));
                data.current_balance = info.players[i].current_balance;
                data.total_balance = info.players[i].total_balance;
                data.deaths = info.players[i].deaths;
                data.position = info.players[i].curr_cooridantes;
                data.server_id = getpid();
                data.game_status = info.game_status;
                data.num = info.players[i].num;
                data.round = info.rounds;
                copy_map(info.map, &info.players[i], data.map);
                players_in_range(data.players_pos, &info.players[i], info.players);
                beasts_in_range(data.beasts_pos, &info.players[i], info.beasts);

                send(info.players[i].psocket, &data, sizeof(struct clients_data), 0);
            }
        }

        info.rounds += 1;
    }

    pthread_cancel(thread_accept);

    dll_clear(info.dropped_treasures);
    free(info.dropped_treasures);

    pthread_mutex_unlock(&mutex);

    endwin();
}