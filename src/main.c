/*
 * File: main.c
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#include<string.h>
#include<stdio.h>

#include"ui/ui.h"
#include"timulate/timulate.h"

#define APPLICATION_NAME "Timulate"

void timulate_main_loop(void)
{
    /*
    timulate_tui_render();
    timulate_tui_input();
    */
    timulate_ui_cl_update();
    timulate_ui_cl_input();
}

int main(int argc, char **argv)
{
    /* testing */
    /* after the players and tournaments are came from bin files */
    uint atp, wta, player, tournament;

    atp = timulate_tour_group_create("ATP", 30, 300);
    wta = timulate_tour_group_create("WTA", 10, 10);

    tournament = timulate_tour_tournaments_append(atp, "fut 1", "city, country", FUTURE, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "fut 2", "city, country", FUTURE, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "fut 3", "city, country", FUTURE, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "fut 4", "city, country", FUTURE, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "fut 5", "city, country", FUTURE, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(atp, "cha 1", "city, country", CHALLANGER, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "cha 2", "city, country", CHALLANGER, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "cha 3", "city, country", CHALLANGER, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "cha 4", "city, country", CHALLANGER, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "cha 5", "city, country", CHALLANGER, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(atp, "250 1", "city, country", ATP_250, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "250 2", "city, country", ATP_250, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "250 3", "city, country", ATP_250, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "250 4", "city, country", ATP_250, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "250 5", "city, country", ATP_250, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(atp, "500 1", "city, country", ATP_500, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "500 2", "city, country", ATP_500, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "500 3", "city, country", ATP_500, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "500 4", "city, country", ATP_500, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "500 5", "city, country", ATP_500, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(atp, "mast 1", "city, country", MASTERS, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "mast 2", "city, country", MASTERS, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "mast 3", "city, country", MASTERS, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "mast 4", "city, country", MASTERS, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "mast 5", "city, country", MASTERS, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(atp, "grand 1", "city, country", GRAND_SLAM, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "grand 2", "city, country", GRAND_SLAM, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "grand 3", "city, country", GRAND_SLAM, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "grand 4", "city, country", GRAND_SLAM, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(atp, "grand 5", "city, country", GRAND_SLAM, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(wta, "fut 1", "city, country", FUTURE, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "fut 2", "city, country", FUTURE, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "fut 3", "city, country", FUTURE, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "fut 4", "city, country", FUTURE, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "fut 5", "city, country", FUTURE, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    tournament = timulate_tour_tournaments_append(wta, "cha 1", "city, country", CHALLANGER, 1);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "cha 2", "city, country", CHALLANGER, 2);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "cha 3", "city, country", CHALLANGER, 3);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "cha 4", "city, country", CHALLANGER, 4);
    timulate_tour_tournaments_setting(tournament, 128);
    tournament = timulate_tour_tournaments_append(wta, "cha 5", "city, country", CHALLANGER, 5);
    timulate_tour_tournaments_setting(tournament, 128);

    /* atp players */
    player = timulate_tour_players_append(atp, "Federer", "Roger");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);
    player = timulate_tour_players_append(atp, "Nadal", "Rafael");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);
    player = timulate_tour_players_append(atp, "Djokovic", "Novak");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);
    player = timulate_tour_players_append(atp, "Domenice", "Thiem");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);

    int i; 
    for (i = 0; i < 200; i++)
    {
        char *dumm = "dumm";
        char name_index[50] = { '\0' };
        char index[10] = { '\0' };
        sprintf(index, "%d", i);
        strcat(name_index, index);
        strcat(name_index, dumm);

        player = timulate_tour_players_append(atp, "Dummy", name_index);
        timulate_tour_players_skill_set(player, 1, 1, 1, 1, 1);
    }

    /* wta players */
    player = timulate_tour_players_append(wta, "Serena", "Wiliams");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);
    player = timulate_tour_players_append(wta, "Venus", "Wiliams");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);
    player = timulate_tour_players_append(wta, "Iga", "Swiatek");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);
    player = timulate_tour_players_append(wta, "Maria", "Sakkari");
    timulate_tour_players_skill_set(player, 99, 99, 99, 99, 99);

    timulate_tour_init();
    timulate_tour_tournaments_sort();
    timulate_tour_week_tournaments_load();
    timulate_tour_week_tournaments_players_signup();

    timulate_ui_cl_init();

    timulate_main_loop_func_set(timulate_main_loop);
    timulate_main_loop_launch();

    return 0;
}
