/*
 * File: ui_cl.c
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#include"../types.h"
#include"../timulate/timulate.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/ioctl.h>

struct {
    uint curr_round;
    uint curr_row_offset;
    char player_name[27];
} TournamentTree = {
    .player_name = { '\0' }
};

void home_page_draw(void);
void tournament_tree_page_draw(void);

void home_page_input(void);
void tournament_tree_page_input(void);

/* pages */
enum {
    HOME_PAGE,
    TOURNAMENT_TREE_PAGE,
};

void (*pages[])(void) = {
    home_page_draw,
    tournament_tree_page_draw,
};

void (*inputs[])(void) = {
    home_page_input,
    tournament_tree_page_input,
};

uint current_page = HOME_PAGE;
uint current_tournament_id = 0;


void ui_cl_update(void)
{
    pages[current_page]();
}

void home_page_input(void)
{
    uint input, id;
    scanf("%d", &input);

    switch (input)
    {
        case 1:
            /* simulate the next day */
            break;
        case 5:
            scanf("%d", &id);
            current_page = TOURNAMENT_TREE_PAGE;
            current_tournament_id = id - 1;
            break;
        case 6:
            exit(0);
            break;
    }
}

void tournament_tree_page_input(void)
{
    char input;
    scanf("%c", &input);

    switch (input)
    {
        case '1':
            current_page = HOME_PAGE;
            TournamentTree.curr_round = 0;
            break;
        case 'f':
            TournamentTree.curr_round++;
            break;
        case 'b':
            TournamentTree.curr_round--;
            break;
        case 'u':
            TournamentTree.curr_row_offset -= 4;
            break;
        case 'd':
            TournamentTree.curr_row_offset += 4;
            break;
    }
}

void ui_cl_input(void)
{
    inputs[current_page]();
}
