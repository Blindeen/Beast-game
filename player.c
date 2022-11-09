#include <ncurses.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "player.h"
#include "UI.h"
#include "dt_structures.h"
#include "map.h"

struct recv_player_data_argument{
    struct clients_data *data;
    int server_socket;
};

void *receive_players_data(void *arg)
{
    struct recv_player_data_argument *data = (struct recv_player_data_argument *)arg;

    while(data->data->game_status)
    {
        if(recv(data->server_socket, data->data, sizeof(struct clients_data), 0) <= 0)
        {
            data->data->game_status = 0;
            break;
        }
    }

    return NULL;
}

void player_loop(int server_socket)
{
    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr, TRUE);

    struct recv_player_data_argument data;
    memset(&data, 0, sizeof(struct recv_player_data_argument));

    struct clients_data playersData;
    data.data = &playersData;
    data.server_socket = server_socket;

    memset(&playersData, 0, sizeof(struct clients_data));
    data.data->game_status = 1;

    pthread_t servers_data;
    pthread_create(&servers_data, NULL, receive_players_data, (void *)&data);

    struct player_packet playerPacket;
    playerPacket.pid = getpid();

    timeout(20);

    while(data.data->game_status)
    {
        for(int i = 0; i < 20; ++i)
        {
            if(playersData.beasts_pos[i].x && playersData.beasts_pos[i].y)
            {
                print_beast(&playersData.beasts_pos[i]);
            }
        }

        if(playersData.server_id)
        {
            print_empty_fields();
            print_player_map(data.data->map, &data.data->position);
            print_player(&data.data->position, data.data->num);
            player_ui(&playersData);
            for(int i = 0; i < 4; ++i)
            {
                if(playersData.players_pos[i].x && playersData.players_pos[i].y)
                {
                    print_player(&playersData.players_pos[i], i+1+'0');
                }
            }
        }
        playerPacket.key = getch();
        if(playerPacket.key == 'q')
        {
            send(server_socket, &playerPacket, sizeof(struct player_packet), 0);
            data.data->game_status = 0;
            break;
        }
        send(server_socket, &playerPacket, sizeof(struct player_packet), 0);
    }

    endwin();
}
