/*
 * File: t_tour.c
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#include"t_internal.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

uint player_reached_rounds[8] = {
    0b1,
    0b10,
    0b100,
    0b1000,
    0b10000,
    0b100000,
    0b1000000,
    0b10000000,
};

const char tournament_types[6][11] = {
    "Grand Slam",
    "Masters",
    "ATP 500",
    "ATP 250",
    "Challanger",
    "Future",
};

TourGlobal tour = {
    .current_year = 0,
    .current_week = 0,
    .running = true,
    .count_groups = 0,
    .tournaments_size = 0,
    .players_size = 0,
};

uint timulate_tour_players_append(uint group_id, char *name, char *pre_name)
{
    static _Bool init = false;
    if (!init)
    {
        tour.players = (Player *)malloc(tour.players_size * sizeof(Player));
        if (tour.players == NULL)
        {
            printf("can't allocate players");
            return -1;
        }
        tour.count_players = 0;

        init = true;
    }

    strncpy(tour.players[tour.count_players].name, name, NAME_SIZE);
    strncpy(tour.players[tour.count_players].pre_name, pre_name, NAME_SIZE);
    tour.players[tour.count_players].points = 0;
    tour.players[tour.count_players].group_id = group_id;

    return tour.count_players++;
}

void timulate_tour_players_skill_set(uint player_id, uint forhand, uint backhand, uint volley, uint serve, uint re_turn)
{
    tour.players[player_id].skills.forhand = forhand;
    tour.players[player_id].skills.backhand = backhand;
    tour.players[player_id].skills.volley = volley;
    tour.players[player_id].skills.serve = serve;
    tour.players[player_id].skills.re_turn = re_turn;
}

uint timulate_tour_tournaments_append(uint group_id, char *name, char *location, uint type, uint week)
{
    static _Bool init;
    if (!init)
    {
        tour.tournaments = malloc(tour.tournaments_size * sizeof(Tournament));
        if (tour.tournaments == NULL)
        {
            printf("can't allocate tournaments");
            exit(1);
        }
        tour.count_tournaments = 0;

        init = true;
    }

    strncpy(tour.tournaments[tour.count_tournaments].name, name, NAME_SIZE);
    strncpy(tour.tournaments[tour.count_tournaments].location, location, NAME_SIZE);
    tour.tournaments[tour.count_tournaments].group_id = group_id;
    tour.tournaments[tour.count_tournaments].type = type;
    tour.tournaments[tour.count_tournaments].week = week;
    tour.tournaments[tour.count_tournaments].player_pool.count = 0;

    return tour.count_tournaments++;
}

void timulate_tour_tournaments_setting(uint id, uint field)
{
    tour.tournaments[id].field = field;
}

uint timulate_tour_group_create(char *name, uint tournaments_size, uint players_size)
{
    strncpy(tour.groups[tour.count_groups].name, name, NAME_SIZE);

    tour.tournaments_size += tournaments_size;
    tour.players_size += players_size;

    return tour.count_groups++;
}

void week_count_tournament_set_zero(Week *weeks)
{
    int i = 52;

    while (i--)
    {
        weeks[i].count_tournaments = 0;
    }
}

void timulate_tour_tournaments_sort(void)
{
    int i;
    for (i = 0; i < tour.count_tournaments; i++)
    {
        Tournament *ptr;

        ptr = &tour.tournaments[i];

        int j;
        for (j = i + 1; j < tour.count_tournaments; j++)
        {
            if (tour.tournaments[j].type * 100 + tour.tournaments[j].week < ptr->type * 100 + ptr->week)
                ptr = &tour.tournaments[j];
        }
        Tournament hold = tour.tournaments[i];
        tour.tournaments[i] = *ptr;
        *ptr = hold;
    }
}

void players_print(void)
{
    int i;
    for (i = 0; i < tour.count_players; i++)
    {
        printf("%s %s\tgroup: %d\n", tour.players[i].name, tour.players[i].pre_name, tour.players[i].group_id);
    }
}

void load_tournaments_for_weeks(Year *year)
{
    int i;
    for (i = 0; i < tour.count_tournaments; i++)
    {
        Week *week = &(year->weeks[tour.tournaments[i].week - 1]);
        week->tournaments[week->count_tournaments] = tour.tournaments[i];
        week->count_tournaments++;
    }
}

void players_signup_for_tournaments(Week *current_week)
{
    int i, j;
    for (i = 0; i < current_week->count_tournaments; i++)
    {
        /* players desicion*/
        for (j = 0; i < tour.count_players; j++)
        {
            /* make desicion */

            /* default sign up */
            /* player id add to pool */
        }
    }
}

Group *internal_tour_group(uint group_id)
{
    return &tour.groups[group_id];
}

void dayofweek_loop(void)
{
    while (tour.current_day <= 7)
    {
        /* play day of current tournament */
        /* store day of current tournament */

        tour.current_day++;
    }
}

void week_tournaments_append(Tournament *template)
{
    static _Bool init = false;
    if (init)
    {
        tour.week_tournaments = malloc(10 * sizeof(Tournament));
        if (tour.week_tournaments == NULL)
        {
            fprintf(stderr, "failed to alloc week_tournaments");
            exit(1);
        }
        init = true;
    }

    if (tour.count_week_tournaments % 10 == 0)
    {
        tour.week_tournaments = realloc(tour.week_tournaments, (tour.count_week_tournaments + 10) * sizeof(Tournament));
    }
    tour.week_tournaments[tour.count_week_tournaments] = *template;
    tour.count_week_tournaments++;
}

void timulate_tour_week_tournaments_load(void)
{
    int i;
    for (i = 0; i < tour.count_tournaments; i++)
    {
        if (tour.current_week == tour.tournaments[i].week)
        {
            week_tournaments_append(&tour.tournaments[i]);
        }
    }
}
void week_tournaments_unload(void)
{
    memset(tour.week_tournaments, 0, tour.count_week_tournaments * sizeof(Tournament));
    tour.count_week_tournaments = 0;
}

uint tournament_first_round_for_reached_rounds(uint field)
{
    switch (field)
    {
        case 128: return PLAYER_POOL_ROUND_128; break;
        case 64: return PLAYER_POOL_ROUND_64; break;
        case 32: return PLAYER_POOL_ROUND_32; break;
        case 16: return PLAYER_POOL_ROUND_16; break;
        case 8: return PLAYER_POOL_ROUND_8; break;
        case 4: return PLAYER_POOL_ROUND_4; break;
        case 2: return PLAYER_POOL_ROUND_2; break;
    }

    return -1;
}

void timulate_tour_week_tournaments_players_signup(void)
{
    int i, j;
    for (i = 0; i < tour.count_week_tournaments; i++)
    {
        for (j = 0; j < tour.count_players; j++)
        {
            if (tour.players[j].group_id == tour.week_tournaments[i].group_id)
            {
                PlayerPool *player_pool = &tour.week_tournaments[i].player_pool;

                if (player_pool->count >= 128)
                    continue;

                player_pool->players_id[player_pool->count] = j;
                player_pool->reached_rounds[player_pool->count] |= player_reached_rounds[tournament_first_round_for_reached_rounds(tour.week_tournaments[i].field)];
                player_pool->count++;
            }
        }
    }
}

void week_loop(void)
{
    while (tour.current_week <= 52)
    {
        /* setting up tournaments of week */
        timulate_tour_week_tournaments_load();
        /* sign up players for tournaments [player pool] */

        tour.current_day = 1;
        dayofweek_loop();
        tour.current_week++;

        week_tournaments_unload();
    }
}

void timulate_year_loop_launch(void)
{
    /* sort tournaments and players list's */
    timulate_tour_tournaments_sort();

    /* debug_tournaments_print(tour.tournaments, tour.count_tournaments); */
    /* debug_players_print(tour.players, tour.count_players); */

    while (tour.running) {
        tour.current_week = 1;
        week_loop();
        tour.current_year++;

        tour.running = false;
    }
}

void timulate_tour_init(void)
{
    tour.current_year = 2010;
    tour.current_week = 1;
    tour.current_day = 1;
}
