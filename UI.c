#include <sys/types.h>
#include <unistd.h>
#include "UI.h"
#include "map.h"

void display_ui(struct server_info *server)
{
    if(server)
    {
        mvprintw(3, 70, "Server's PID: %lu\n", getpid());
        mvprintw(4, 73, "Campsite X/Y: %02d/%02d\n", CAMPSITE_X, CAMPSITE_Y);
        mvprintw(5, 73, "Round number: %lu\n", server->rounds);

        mvprintw(7, 70, "Parameter:\n");
        mvprintw(9, 73, "PID     \n");
        mvprintw(10, 73, "Type       \n");
        mvprintw(11, 73, "Curr X/Y    \n");
        mvprintw(12, 73, "Deaths      \n");

        mvprintw(14, 73, "Coins");
        mvprintw(15, 77, "carried \n");
        mvprintw(16, 77, "brought \n");

        for(int i = 0; i < 4; ++i)
        {
            mvprintw(7, 85+10*i, "Player%d", i+1);
            if(server->players[i].pid)
            {
                mvprintw(9, 85+10*i, "%d", server->players[i].pid);
                mvprintw(10, 85+10*i, "HUMAN");
                mvprintw(11, 85+10*i, "%02d/%02d", server->players[i].curr_cooridantes.x, server->players[i].curr_cooridantes.y);
                mvprintw(12, 85+10*i, "%d", server->players[i].deaths);

                mvprintw(15, 85+10*i, "%d", server->players[i].current_balance);
                mvprintw(16, 85+10*i, "%d", server->players[i].total_balance);
            }
            else
            {
                mvprintw(9, 85+10*i, "-");
                mvprintw(10, 85+10*i, "-");
                mvprintw(11, 85+10*i, "--/--");
                mvprintw(12, 85+10*i, "-");

                mvprintw(15, 85+10*i, "-");
                mvprintw(16, 85+10*i, "-");
            }
        }

        mvprintw(18, 69, "Legend:\n");

        init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
        init_pair(MONEY, COLOR_WHITE, COLOR_GREEN);
        init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(CAMPSITE, COLOR_YELLOW, COLOR_RED);
        init_pair(BEAST, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(PLAYER)); mvprintw(19, 69, "1234"); attroff(COLOR_PAIR(PLAYER)); mvprintw(19, 73, " - players\n");
        attron(COLOR_PAIR(WALL)); mvprintw(20, 69, "W"); attroff(COLOR_PAIR(WALL)); mvprintw(20, 73, " - wall\n");
        mvprintw(21, 69, "#"); mvprintw(21, 73, " - bushes (slow down)\n");
        attron(COLOR_PAIR(BEAST)); mvprintw(22, 69, "*"); attroff(COLOR_PAIR(BEAST)); mvprintw(22, 73, " - enemy\n");
        attron(COLOR_PAIR(MONEY)); mvprintw(23, 69, "c"); attroff(COLOR_PAIR(MONEY)); mvprintw(23, 73, " - one coin"); attron(COLOR_PAIR(MONEY)); mvprintw(23, 90, "D"); attroff(COLOR_PAIR(MONEY)); mvprintw(23, 91, " - dropped treasure\n");
        attron(COLOR_PAIR(MONEY)); mvprintw(24, 69, "C"); attroff(COLOR_PAIR(MONEY)); mvprintw(24, 73, " - treasure (10 coins)\n");
        attron(COLOR_PAIR(MONEY)); mvprintw(25, 69, "T"); attroff(COLOR_PAIR(MONEY)); mvprintw(25, 73, " - large treasure (50 coins)\n");
        attron(COLOR_PAIR(CAMPSITE)); mvprintw(26, 69, "A"); attroff(COLOR_PAIR(CAMPSITE)); mvprintw(26, 73, " - campsite");

        refresh();
    }
}

void player_ui(struct clients_data *playersData)
{
    if(playersData)
    {
        mvprintw(3, 70, "Server's PID: %d\n", playersData->server_id);
        if(is_camp_in_range(playersData->map))
        {
            mvprintw(4, 73, "Campsite X/Y: %02d/%02d\n", CAMPSITE_X, CAMPSITE_Y);
        }
        else
        {
            mvprintw(4, 73, "Campsite X/Y: UNKNOWN\n");
        }
        mvprintw(5, 73, "Round number: %lu\n", playersData->round);

        mvprintw(7, 70, "Player:\n");
        mvprintw(8, 73, "Number:     %c\n", playersData->num);
        mvprintw(9, 73, "Type:       HUMAN\n");
        mvprintw(10, 73, "Curr X/Y    %02d/%02d\n", playersData->position.x, playersData->position.y);
        mvprintw(11, 73, "Deaths      %d\n", playersData->deaths);

        mvprintw(13, 73, "carried %d\n", playersData->current_balance);
        mvprintw(14, 73, "brought %d\n", playersData->total_balance);



        mvprintw(18, 69, "Legend:\n");

        init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
        init_pair(MONEY, COLOR_WHITE, COLOR_GREEN);
        init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(CAMPSITE, COLOR_YELLOW, COLOR_RED);
        init_pair(BEAST, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(PLAYER)); mvprintw(19, 69, "1234"); attroff(COLOR_PAIR(PLAYER)); mvprintw(19, 73, " - players\n");
        attron(COLOR_PAIR(WALL)); mvprintw(20, 69, "W"); attroff(COLOR_PAIR(WALL)); mvprintw(20, 73, " - wall\n");
        mvprintw(21, 69, "#"); mvprintw(21, 73, " - bushes (slow down)\n");
        attron(COLOR_PAIR(BEAST)); mvprintw(22, 69, "*"); attroff(COLOR_PAIR(BEAST)); mvprintw(22, 73, " - enemy\n");
        attron(COLOR_PAIR(MONEY)); mvprintw(23, 69, "c"); attroff(COLOR_PAIR(MONEY)); mvprintw(23, 73, " - one coin"); attron(COLOR_PAIR(MONEY)); mvprintw(23, 90, "D"); attroff(COLOR_PAIR(MONEY)); mvprintw(23, 91, " - dropped treasure\n");
        attron(COLOR_PAIR(MONEY)); mvprintw(24, 69, "C"); attroff(COLOR_PAIR(MONEY)); mvprintw(24, 73, " - treasure (10 coins)\n");
        attron(COLOR_PAIR(MONEY)); mvprintw(25, 69, "T"); attroff(COLOR_PAIR(MONEY)); mvprintw(25, 73, " - large treasure (50 coins)\n");
        attron(COLOR_PAIR(CAMPSITE)); mvprintw(26, 69, "A"); attroff(COLOR_PAIR(CAMPSITE)); mvprintw(26, 73, " - campsite");

        refresh();
    }
}