#include <ncurses.h>
#include <sys/socket.h>
#include "player.h"
#include "UI.h"

void player_loop(int server_socket)
{
    initscr();
    curs_set(0);
    char direction;

    while(1)
    {
//        keypad(stdscr, TRUE);
        direction = getch();
        if(direction == 'q')
        {
            break;
        }
        else
        {
            send(server_socket, &direction, sizeof(direction), 0);
        }
    }

    endwin();
}
