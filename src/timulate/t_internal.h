/*
 * File: t_internal.h
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#ifndef T_INTERNAL_H
#define T_INTERNAL_H

#include"../types.h"

#define NAME_SIZE 250

#define WEEK_TOURNAMENT_MAX 10
#define TOURNAMENTS_MAX_PLAYERS 128

enum {
    PLAYER_POOL_ROUND_128,
    PLAYER_POOL_ROUND_64,
    PLAYER_POOL_ROUND_32,
    PLAYER_POOL_ROUND_16,
    PLAYER_POOL_ROUND_8,
    PLAYER_POOL_ROUND_4,
    PLAYER_POOL_ROUND_2,
    PLAYER_POOL_WINNER,
};

extern uint player_reached_rounds[8];

/* Skillset of a Player in a range from 0 to 1000 */
typedef struct {
    uint forhand;
    uint backhand;
    uint volley;
    uint serve;
    uint re_turn;
} Skill;

typedef struct {
    char name[NAME_SIZE];
    char pre_name[NAME_SIZE];
    uint points;
    uint group_id;
    Skill skills;
    uint *activity[2];
} Player;

typedef struct {
    uint players_id[TOURNAMENTS_MAX_PLAYERS];
    uint8 reached_rounds[TOURNAMENTS_MAX_PLAYERS];
    uint count;
} PlayerPool;

typedef struct {
    uint8 wildcards;
    uint8 set_players;
} TSetting;

typedef struct {
    char name[NAME_SIZE];
    char location[NAME_SIZE];
    uint group_id;
    uint type;
    uint week;
    PlayerPool player_pool;
    uint field;
    TSetting settings;
} Tournament;

typedef struct {
    Tournament tournaments[WEEK_TOURNAMENT_MAX];
    uint count_tournaments;
} Week;

typedef struct {
    Week weeks[52];
    uint year;
} Year;

typedef struct {
    uint id;
    char name[NAME_SIZE];
} Group;

extern const char tournament_types[6][11];

typedef struct {
    uint current_year;
    uint current_week;
    uint current_day;
    uint start_year;
    Group groups[10];
    uint count_groups;
    Tournament *tournaments;
    uint count_tournaments;
    Player *players;
    uint count_players;
    uint tournaments_size;
    uint players_size;
    Tournament *week_tournaments;
    uint count_week_tournaments;
    _Bool running;
} TourGlobal;

extern TourGlobal tour; 

/* debbuging functions */
void debug_tournaments_print(Tournament *tournaments, uint count_tournaments);
void debug_players_print(Player *players, uint count_players);

/* functions */
Group *internal_tour_group_get(uint group_id);

Player *player_pool_player_by_round(PlayerPool *player_pool, uint round, uint index);

#endif
