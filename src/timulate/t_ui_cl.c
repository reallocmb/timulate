/*
 * File: t_ui_cl.c
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<unistd.h>
#include<sys/ioctl.h>

#include"t_internal.h"

uint tournament_selected = 0;

enum {
    PAGE_HOME,
    PAGE_TOURNAMENT_TREE,
};

void (*pages_draw_func[2])(void);

uint curr_page = PAGE_HOME;
uint tournament_tree_row_offset = 0;
uint tournament_tree_rounds_offset = 0;

struct {
    void (*page_draw_func)(void);
} Ui_Cl;

void home_page_draw(void)
{
    system("clear");
    printf("Day/Week/Year %d:%d:%d\n\n",
            tour.current_day,
            tour.current_week,
            tour.current_year);

    printf("Week Tournaments:\n");

    int i;
    for (i = 0; i < tour.count_week_tournaments; i++)
    {

        Tournament *tournament = &tour.week_tournaments[i];
        uint type = tournament->type;
        uint group_id = tournament->group_id;

        printf("%4d. %s\t%s\t%s\t%s",
                i + 1,
                tour.groups[group_id].name,
                tournament->name,
                tournament->location,
                tournament_types[type]);
        putchar('\n');
    }

    /* options */
    printf("--User--\n");
    printf("1. Next Day Sim\n");
    printf("2. Next Week Sim\n");
    printf("3. Previous Day\n");
    printf("4. Previous Week\n");
    printf("5. Show Tournament Tree [id]\n");
    printf("6. Exit\n");
}

void window_dimension(uint *row, uint *col)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    *row = w.ws_row;
    *col = w.ws_col;
}

uint field_amount_rounds(uint field)
{
    uint rounds = 0;
    while (field > 1)
    {
        field /= 2;
        rounds++;
    }

    return rounds + 1;

}

void page_content_insert_str(char **page_content, char *str, uint y, uint x)
{
    uint i;
    for (i = 0; i < strlen(str); i++)
        page_content[y][x + i] = str[i];
}

void tournament_tree_page_draw(void)
{
    system("clear");

    Tournament *tournament = &tour.week_tournaments[tournament_selected];

    uint i, j;

    /* title */
    char page_title[50] = { '\0' };
    sprintf(page_title, "%d. %s %s %s %s",
            tournament_selected + 1,
            tour.groups[tournament->group_id].name,
            tournament->name,
            tournament->location,
            tournament_types[tournament->group_id]);

    /* insert page */

    /* player insert */
    uint field = tournament->field;
    uint amount_rounds = field_amount_rounds(field);

    uint obj_length = 28;

    uint tree_x = amount_rounds * obj_length;
    uint tree_y = field * 2;

    /* allocate page_content */
    char **page_content = malloc(tree_y * sizeof(char *));
    i = tree_y;
    while (i--)
        page_content[i] = malloc(tree_x * sizeof(char));

    /* clear page_content */
    for (i = 0; i < tree_y; i++)
        for (j = 0; j < tree_x; j++)
            page_content[i][j] = ' ';

    uint x_offset = 0;
    uint y_offset = 0;

    uint player_pos_x = 0;
    uint player_pos_y = 0;

    uint players_id_i = 0;

    uint walls = 1;

    /* insert tree content */
    for (i = 0; i < amount_rounds; i++) /* rounds */
    {
        for (j = 0; j < tree_y;)
        {
            /* player */
            char player_name[50];
            Player *player = NULL;

            while (players_id_i < tournament->field)
            {
                if (tournament->player_pool.reached_rounds[players_id_i] & player_reached_rounds[i])
                {
                    player = &tour.players[tournament->player_pool.players_id[players_id_i]];
                    players_id_i++;
                    break;
                }
                players_id_i++;
            }

            if (player == NULL)
                sprintf(player_name, "No Player");
            else
                sprintf(player_name, "%s %s", player->name, player->pre_name);

            player_pos_x = 1 + x_offset;
            player_pos_y = j + y_offset;

            page_content_insert_str(page_content, player_name, player_pos_y, player_pos_x);
            j++; /* offset to line */
            /* line under player */
            page_content_insert_str(page_content, "----------------------------", j + y_offset, x_offset);

            /* result */
            char *result = "0/0 0/0 0/0 0/0 0/0";
            if (i > 0)
                page_content_insert_str(page_content, result, player_pos_y + 2, player_pos_x);
            /* walls */
            if (walls && i < amount_rounds - 1)
            {
                uint wall_pos_x = x_offset + obj_length - 1;
                uint wall_pos_y = j + y_offset + 1;

                uint wall_amount = y_offset * 2 + 1;
                while (wall_amount--)
                    page_content_insert_str(page_content, "|", wall_pos_y + wall_amount, wall_pos_x);
                walls = 0;
            }
            else
                walls = 1;

            /* finish */
            j += y_offset * 2 + 1;
        }
        walls = 1;
        y_offset = 2 * y_offset + 1;
        players_id_i = 0;
        x_offset += obj_length;
    }

    /* information for page draw */
    uint window_rows = 0;
    uint window_cols = 0;
    uint8 amount_options = 7;
    window_dimension(&window_rows, &window_cols);

    uint rows = window_rows - amount_options - 2;
    uint cols = window_cols;

    /* draw title */
    printf("%s", page_title);
    putchar('\n');
    putchar('\n');


    /* draw page content */
    for (i = tournament_tree_row_offset; i < rows + tournament_tree_row_offset; i++)
    {
        if (i < tree_y)
            for (j = tournament_tree_rounds_offset * obj_length; j < cols + tournament_tree_rounds_offset * obj_length; j++)
            {
                if (j < tree_x)
                    putchar(page_content[i][j]);
                else
                    putchar('#');
            }
        else
            for (j = 0; j < cols; j++)
                putchar('#');

        putchar('\n');
    }

    /* draw options */
    printf("--User--\n");
    printf("1. Back\n");
    printf("f. Forward Rounds\n");
    printf("b. Backwards Rounds\n");
    printf("u. Up\n");
    printf("d. Down\n");
}

void timulate_ui_cl_update(void)
{
    pages_draw_func[curr_page]();
}

void timulate_ui_cl_input(void)
{
    char c = '\0';
    uint id;

    scanf("%c", &c);

    if (curr_page == 0)
    {
        switch (c)
        {
            case '1':
                /* simulate the next day */
                break;
            case '5':
                scanf("%d", &id);
                tournament_selected = id - 1;
                curr_page = PAGE_TOURNAMENT_TREE;
                break;
            case '6':
                exit(0);
                break;
        }
    }

    if (curr_page == 1)
    {
        switch (c)
        {
            case '1': curr_page = PAGE_HOME; break;
            case 'f': tournament_tree_rounds_offset++; break;
            case 'b': tournament_tree_rounds_offset--; break;
            case 'u': tournament_tree_row_offset -= 10; break;
            case 'd': tournament_tree_row_offset += 10; break;
        }
    }
}

void timulate_ui_cl_init(void)
{
    pages_draw_func[0] = home_page_draw;
    pages_draw_func[1] = tournament_tree_page_draw;
}
