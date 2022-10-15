#include "UI.h"

void display_ui()
{
    mvprintw(3, 70, "Server's PID: -\n");
    mvprintw(4, 73, "Campsite X/Y: unknown\n");
    mvprintw(5, 73, "Round number: 32234\n");

    mvprintw(7, 70, "Player:\n");
    mvprintw(8, 73, "Number:     3\n");
    mvprintw(9, 73, "Type:       HUMAN\n");
    mvprintw(10, 73, "Curr X/Y    04/03\n");
    mvprintw(11, 73, "Deaths      0\n");

    mvprintw(13, 73, "Coins found 0\n");
    mvprintw(14, 73, "Coins brought 0\n");



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