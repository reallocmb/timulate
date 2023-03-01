/*
 * File: timulate.h
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#ifndef TIMULATE_H
#define TIMULATE_H

#include"../types.h"

/* Tournament Types */
enum {
    GRAND_SLAM,
    MASTERS,
    ATP_500,
    ATP_250,
    CHALLANGER,
    FUTURE,
};

void timulate_tour_init(void); /* Initialation of the Library. */

/* Tour global */
uint timulate_tour_current_day(void); /* Returns the current day */
uint timulate_tour_current_week(void); /* Returns the current week */
uint timulate_tour_current_year(void); /* Reutrns the current year */

/* Groups */
uint timulate_tour_group_create(char *name, uint tournaments_size, uint players_size); /* Create a Group Returns the index for Tour.groups[index] array */
char *timulate_tour_group_name(uint id); /* Returns group name from the Tour.groups[id] */

/* Tournaments */
void timulate_tour_tournaments_sort(void); /* Sort the Tour.tournaments array. So the big tournaments came first */
uint timulate_tour_tournaments_append(uint group_id, char *name, char *location, uint type, uint week); /* Create a new Tournament and store it in Tour.tournaments array */
void timulate_tour_tournaments_setting(uint id, uint field); /* Set the setting of a existing Tournament in Tour.tournaments array */
uint timulate_tour_count_week_tournaments(void); /* Returns the value of Tour.count_week_tournaments */

/* Tournament Types */
const char *timulate_tournament_types(uint type); /* Returns the String of the tournament type given by 'type' */

/* Tour.week_tournaments */
void timulate_tour_week_tournaments_load(void); /* Load all the Tournaments from Tour.tournaments which take place in the current week to the Tour.week_tournaments */ 
void timulate_tour_week_tournaments_players_signup(void); /* Fill the Player Pool with the players they play the Tournaments in the Tour.week_tournaments array */

uint timulate_tour_week_tournaments_group_id(uint id); /* Returns the value of Tour.week_tournaments.group_id */
char *timulate_tour_week_tournaments_name(uint id); /* Returns the value of Tour.week_tournaments.name */
char *timulate_tour_week_tournaments_location(uint id); /* Returns the value of Tour.week_tournaments.location */
uint timulate_tour_week_tournaments_type(uint id); /* Returns the value of Tour.week_tournaments.type */
uint timulate_tour_week_tournaments_field(uint id); /* Returns the value of Tour.week_tournaments.field */
uint *timulate_tour_week_tournaments_player_pool(uint id); /* Returns the value of Tour.week_tournaments.player_pool */
uint8 *timulate_tour_week_tournaments_player_pool_rounds(uint id); /* Returns the value of Tour.week_tournaments.player_pool_rounds */
uint timulate_tour_week_tournaments_count_player_pool(uint id); /* Returns the value of Tour.week_tournaments.count_player_pool */
uint timulate_tour_week_tournaments_player_pool_current_player_id(uint index, uint round); /* Returns the id for the player_pool array[id] whitch is in the current 'round' and current 'index' from the top */

/* Players */
uint timulate_tour_players_append(uint group_id, char *name, char *pre_name); /* Create a new player and store it in Tour.players array */
void timulate_tour_players_skill_set(uint player_id, uint forhand, uint backhand, uint volley, uint serve, uint re_turn); /* Set the Skill values of a existing Player in the Tour.players array */

/* Tour.players */
char *timulate_tour_players_name(uint id); /* Returns the name of the player in Tour.players[id] */
char *wimulate_tour_players_pre_name(uint id); /* Returns the pre name of the player in Tour.players[id] */

/* User Interface */
void timulate_ui_cl_init(void); /* Initialization of User Interface */
void timulate_ui_cl_update(void); /* Update the User Interface */
void timulate_ui_cl_input(void); /* Handle the User Input */

/* TUI */
void timulate_tui_render(void);
void timulate_tui_input(void);

/* Main */
void timulate_main_loop_func_set(void *func); /* Set the function for the Main loop */
void timulate_main_loop_launch(void); /* Launch the Main loop function */

#endif
