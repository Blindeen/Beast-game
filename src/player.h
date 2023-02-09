#ifndef GAME_BEAST_PLAYER_H
#define GAME_BEAST_PLAYER_H

#include "point.h"

void *receive_players_data(void *arg);
void player_loop(int server_socket);

#endif
