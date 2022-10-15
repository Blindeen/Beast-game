#include <stdio.h>
#include <ncurses.h>
#include "map.h"
#include "UI.h"
#include "player.h"

int main() {

    char map[128][129];
    struct player_t player1;
    initscr();
    curs_set(0);
    map_load(map);
    map_print(map);
    display_ui();
    initialize_player(&player1);
    spawn_player(&player1, map);
    map_print(map);
    display_ui();
    char c = getch();
    if(c == 'q' || c == 'Q')
    {
        endwin();
    }
    return 0;
}
