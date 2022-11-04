#ifndef GAME_BEAST_DT_STRUCTURES_H
#define GAME_BEAST_DT_STRUCTURES_H

//Contains server's received data
struct player_packet{
    pid_t pid;
    int key;
};

//Player's data to sending from server
struct clients_data{
    char map[5][6];
    struct point_t position;
    unsigned int deaths;
    unsigned int current_balance;
    unsigned int total_balance;
    unsigned int round;
    pid_t server_id;
    char num;

    unsigned int game_status:1;
    struct point_t players_pos[4];
    struct point_t beasts_pos[20];
};

#endif
