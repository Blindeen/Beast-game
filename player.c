#include <ncurses.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include "player.h"
#include "UI.h"
#include "dt_structures.h"

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
    struct clients_data playersData;
    data.data = &playersData;
    data.server_socket = server_socket;

    memset(&playersData, 0, sizeof(struct clients_data));
    data.data->game_status = 1;

    pthread_t servers_data;
    pthread_create(&servers_data, NULL, receive_players_data, (void *)&data);

    struct player_packet playerPacket;
    playerPacket.conn_status = 1;
    playerPacket.pid = getpid();

    timeout(50);

    while(data.data->game_status)
    {
        player_ui(&playersData);
        playerPacket.key = getch();
        if(playerPacket.key == 'q')
        {
            send(server_socket, &playerPacket, sizeof(struct player_packet), 0);
            break;
        }
        send(server_socket, &playerPacket, sizeof(struct player_packet), 0);
    }

    endwin();
}
