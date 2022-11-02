#include "map.h"
#include <ncurses.h>
#include <string.h>

int map_load(char map[][129])
{
    FILE *f = fopen("map1.txt", "rt");
    if(f == NULL)
    {
        return 0;
    }

    char new_line[MAX_MAP_WIDTH+1];
    for(int i = 0; fgets(new_line, sizeof(new_line), f); ++i)
    {
        strcpy(map[i], new_line);
    }

    return 1;
}

void map_print(char map[][129])
{
    init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(MONEY, COLOR_WHITE, COLOR_GREEN);
    init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(CAMPSITE, COLOR_YELLOW, COLOR_RED);

    for(int i = 0; i < MAP_HEIGHT; ++i)
    {
        for(int j = 0; j < MAP_WIDTH; ++j)
        {
            switch (map[i][j]) {
                case 'W':
                {
                    attron(COLOR_PAIR(WALL));
                    mvaddch(3+i, 3+j, map[i][j]);
                    attroff(COLOR_PAIR(WALL));
                }
                    break;
                case 'T': case 'C': case 'c': case 'D':
                {
                    attron(COLOR_PAIR(MONEY));
                    mvaddch(3+i, 3+j, map[i][j]);
                    attroff(COLOR_PAIR(MONEY));
                }
                    break;
                case 'A':
                {
                    attron(COLOR_PAIR(CAMPSITE));
                    mvaddch(3+i, 3+j, map[i][j]);
                    attroff(COLOR_PAIR(CAMPSITE));
                }
                    break;
                default:
                {
                    mvaddch(3+i, 3+j, map[i][j]);
                }
            }
        }
    }

    refresh();

}


void print_player(struct point_t *coords, char num)
{
    if(coords)
    {
        init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
        attron(COLOR_PAIR(PLAYER));
        mvaddch(3+coords->y, 3+coords->x, num);
        attroff(COLOR_PAIR(PLAYER));

    }

    refresh();
}

void copy_map(char map[][MAX_MAP_WIDTH+1], struct player_t *player, char o_map[][6])
{
    int l_corner_x = player->curr_cooridantes.x - 2;
    int l_corner_y = player->curr_cooridantes.y - 2;

    if(l_corner_x < 0)
    {
        l_corner_x = 0;
    }
    else if(l_corner_x > 51)
    {
        l_corner_x = player->curr_cooridantes.x;
    }

    if(l_corner_y < 0)
    {
        l_corner_y = 0;
    }
    else if(l_corner_y > 24)
    {
        l_corner_y = player->curr_cooridantes.y;
    }

    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            o_map[i][j] = map[l_corner_y+i][l_corner_x+j];
        }
    }

}

void print_player_map(char map[][6], struct point_t *coords)
{
    init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(MONEY, COLOR_WHITE, COLOR_GREEN);
    init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(CAMPSITE, COLOR_YELLOW, COLOR_RED);

    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            switch (map[i][j]) {
                case 'W':
                {
                    attron(COLOR_PAIR(WALL));
                    mvaddch(3+i+coords->y-2, 3+j+coords->x-2, map[i][j]);
                    attroff(COLOR_PAIR(WALL));
                }
                    break;
                case 'T': case 'C': case 'c': case 'D':
                {
                    attron(COLOR_PAIR(MONEY));
                    mvaddch(3+i+coords->y-2, 3+j+coords->x-2, map[i][j]);
                    attroff(COLOR_PAIR(MONEY));
                }
                    break;
                case 'A':
                {
                    attron(COLOR_PAIR(CAMPSITE));
                    mvaddch(3+i+coords->y-2, 3+j+coords->x-2, map[i][j]);
                    attroff(COLOR_PAIR(CAMPSITE));
                }
                    break;
                default:
                {
                    mvaddch(3+i+coords->y-2, 3+j+coords->x-2, map[i][j]);
                }
            }
        }
    }

    refresh();
}

int is_camp_in_range(char map[][6])
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(map[i][j] == 'A')
            {
                return 1;
            }
        }
    }

    return 0;
}

void print_empty_fields()
{
    for(int i = 0; i < MAP_HEIGHT; ++i)
    {
        for(int j = 0; j < MAP_WIDTH; ++j)
        {
            mvaddch(3+i, 3+j, ' ');
        }
    }

    refresh();
}