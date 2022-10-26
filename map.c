#include "map.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

struct map_t *map_init()
{
    struct map_t *map_structure = (struct map_t *) calloc(1, sizeof(struct map_t));
    if(!map_structure)
    {
        return NULL;
    }

    map_structure->width = 52;
    map_structure->height = 25;

    char **map = (char **) calloc(map_structure->height, sizeof(char *));
    if(map == NULL)
    {
        free(map_structure);
        return NULL;
    }

    for(int i = 0; i < map_structure->height; ++i)
    {
        *(map+i) = (char *) calloc(map_structure->width+1, sizeof(char));
        if(*(map+i) == NULL)
        {
            for(int j = 0; j < i; ++j)
            {
                free(*(map+i));
            }
            free(map);
            free(map_structure);
            return NULL;
        }
    }

    FILE *f = fopen("map0.txt", "rt");
    if(f == NULL)
    {
        free(map);
        free(map_structure);
        return NULL;
    }

    char new_line[MAX_MAP_WIDTH+1];
    for(int i = 0; fgets(new_line, sizeof(new_line), f); ++i)
    {
        strcpy(*(map+i), new_line);
    }

    map_structure->map = map;

    fclose(f);

    return map_structure;
}

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
    start_color();
    init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(MONEY, COLOR_WHITE, COLOR_GREEN);
    init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(CAMPSITE, COLOR_YELLOW, COLOR_RED);

    for(int i = 0; i < 25; ++i)
    {
        for(int j = 0; j < 52; ++j)
        {
            switch (map[i][j]) {
                case 'W':
                {
                    attron(COLOR_PAIR(WALL));
                    mvaddch(3+i, 3+j, map[i][j]);
                    attroff(COLOR_PAIR(WALL));
                }
                    break;
                case 'T': case 't': case 'c':
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
                case '1': case '2':
                {
                    attron(COLOR_PAIR(PLAYER));
                    mvaddch(3+i, 3+j, map[i][j]);
                    attroff(COLOR_PAIR(PLAYER));
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

void map_display(struct map_t *map)
{
    if(map != NULL)
    {
        init_pair(WALL, COLOR_WHITE, COLOR_WHITE);
        init_pair(MONEY, COLOR_WHITE, COLOR_GREEN);
        init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(CAMPSITE, COLOR_YELLOW, COLOR_RED);

        for(int i = 0; i < 25; ++i)
        {
            for(int j = 0; j < 52; ++j)
            {
                switch (*(*(map->map+i)+j)) {
                    case 'W':
                    {
                        attron(COLOR_PAIR(WALL));
                        mvaddch(3+i, 3+j, *(*(map->map+i)+j));
                        attroff(COLOR_PAIR(WALL));
                    }
                        break;
                    case 'T': case 't': case 'c':
                    {
                        attron(COLOR_PAIR(MONEY));
                        mvaddch(3+i, 3+j, *(*(map->map+i)+j));
                        attroff(COLOR_PAIR(MONEY));
                    }
                        break;
                    case 'A':
                    {
                        attron(COLOR_PAIR(CAMPSITE));
                        mvaddch(3+i, 3+j, *(*(map->map+i)+j));
                        attroff(COLOR_PAIR(CAMPSITE));
                    }
                        break;
                    default:
                    {
                        mvaddch(3+i, 3+j, *(*(map->map+i)+j));
                    }
                }
                refresh();
            }
        }
    }
}

void print_player(struct player_t *player)
{
    if(player)
    {
        init_pair(PLAYER, COLOR_WHITE, COLOR_MAGENTA);
        attron(COLOR_PAIR(PLAYER));
        mvaddch(3+player->curr_cooridantes.y, 3+player->curr_cooridantes.x, player->num);
        attroff(COLOR_PAIR(PLAYER));

        refresh();
    }
}