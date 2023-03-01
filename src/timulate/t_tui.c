/*
 * File: t_tui.c
 * Autor: Matthias Brunner
 * Copyright © by Matthias Brunner
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<unistd.h>

void tui_size(uint16_t *rows, uint16_t *cols)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
}

void timulate_tui_render(void)
{
    system("clear");
    uint16_t rows, cols;
    tui_size(&rows, &cols);
    char window[rows * cols];
    memset(window, '#', rows * cols);

    /* render window */
    uint16_t r, c;
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            putchar(window[r * cols + c]);
        }
    }
}

static struct termios new_io;
static struct termios old_io;

int cbreak(int fd)
{
   /*Sichern unseres Terminals*/
   if((tcgetattr(fd, &old_io)) == -1)
      return -1;
   new_io = old_io;
   /* Wir verändern jetzt die Flags für den cbreak-Modus. */
   new_io.c_lflag = new_io.c_lflag & ~(ECHO|ICANON);
   new_io.c_cc[VMIN] = 1;
   new_io.c_cc[VTIME]= 0;

   /*Jetzt setzen wir den cbreak-Modus*/
   if((tcsetattr(fd, TCSAFLUSH, &new_io)) == -1)
      return -1;
   return 1;
}

int getch(void)
{
   int c;

   if(cbreak(STDIN_FILENO) == -1) {
      printf("Fehler bei der Funktion cbreak ... \n");
      exit(EXIT_FAILURE);
   }
   c = getchar();
   /* alten Terminal-Modus wiederherstellen */
   tcsetattr(STDIN_FILENO, TCSANOW, &old_io);
   return c;
}

void timulate_tui_input(void)
{
    getch();
}
