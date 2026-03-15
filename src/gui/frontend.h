#ifndef _H
#define _H

#include <ncurses.h>

#include "../common_objects/defines.h"
#undef border

void print_overlay(void);
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_pause();
void print_game(GameInfo_t info);
void printNextfigure(GameInfo_t info);
void print_stats(GameInfo_t info);
void print_start();
void print_gameover(int *score);
void print_win();
void print_screen(GameInfo_t info);
UserAction_t get_signal();

#endif