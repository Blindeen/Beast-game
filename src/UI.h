#ifndef GAME_BEAST_UI_H
#define GAME_BEAST_UI_H

#include <ncurses.h>
#include "player.h"
#include "server.h"
#include "dt_structures.h"

void display_ui(struct server_info *server); //Displays server's interface
void player_ui(struct clients_data *playersData); //Displays player's interface

#endif
