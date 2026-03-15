#include "frontend.h"

void print_overlay(void) {
  print_rectangle(0, BOARD_N + 1, 0, BOARD_M + 1);
  print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3);

  print_rectangle(1, 3, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(4, 8, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(9, 14, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(15, 20, BOARD_M + 3, BOARD_M + HUD_WIDTH + 2);

  MVPRINTW(2, BOARD_M + 5, "LEVEL: ");
  MVPRINTW(5, BOARD_M + 5, "SCORE: ");
  MVPRINTW(7, BOARD_M + 5, "RECORD: ");
  MVPRINTW(10, BOARD_M + 5, "NEXT: ");
  MVPRINTW(16, BOARD_M + 5, "arrows - move");
  MVPRINTW(18, BOARD_M + 5, "space - action");
  MVPRINTW(17, BOARD_M + 5, "p\\P - pause");
  MVPRINTW(19, BOARD_M + 5, "end - exit");
  MVPRINTW(BOARD_N / 2, (BOARD_M - BANNER_LEN) / 2 + 1, INTRO_MESSAGE);
}

void print_stats(GameInfo_t info) {
  MVPRINTW(2, BOARD_M + 13, "%05d", info.level);
  MVPRINTW(5, BOARD_M + 13, "%05d", info.score);
  MVPRINTW(7, BOARD_M + 13, "%d", info.high_score);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++)
    MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int j = top_y + 1; j < bottom_y; j++) {
    MVADDCH(j, left_x, ACS_VLINE);
    MVADDCH(j, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++)
    MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void print_pause() {
  mvprintw(8, 3, "--------------------");
  mvprintw(9, 11, "PAUSE");
  mvprintw(10, 3, "--------------------");
  mvprintw(15, 8, "IF YOU WANT");
  mvprintw(16, 8, "TO CONTINUE");
  mvprintw(17, 8, "PRESS ENTER");
}

void print_game(GameInfo_t info) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int sym = 1;
      if (info.field[i][j] == 1) {
        sym = 3;
        attron(COLOR_PAIR(sym));
        MVPRINTW(i + 1, j * 2 + 1, "%c", '[');
        MVPRINTW(i + 1, j * 2 + 2, "%c", ']');
        attroff(COLOR_PAIR(sym));
      } else if (info.field[i][j] == 2) {
        sym = 2;
        attron(COLOR_PAIR(sym));
        MVPRINTW(i + 1, j * 2 + 1, "%c", '[');
        MVPRINTW(i + 1, j * 2 + 2, "%c", ']');
        attroff(COLOR_PAIR(sym));
      } else {
        attron(COLOR_PAIR(sym));
        MVPRINTW(i + 1, j * 2 + 1, "%c", '.');
        MVPRINTW(i + 1, j * 2 + 2, "%c", ' ');
        attroff(COLOR_PAIR(1));
      }
    }
  }
}

void printNextfigure(GameInfo_t info) {
  for (int i = 1; i < FIGURE_SIZE - 1; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (info.next[i][j] != 0) {
        attron(COLOR_PAIR(4));
        MVPRINTW(i + 10, j * 2 + BOARD_M + 7, "%c", '[');
        MVPRINTW(i + 10, j * 2 + BOARD_M + 7 + 1, "%c", ']');
        attroff(COLOR_PAIR(4));
      } else {
        MVPRINTW(i + 10, j * 2 + BOARD_M + 7, "%c", ' ');
        MVPRINTW(i + 10, j * 2 + BOARD_M + 7 + 1, "%c", ' ');
      }
    }
  }
}

void print_gameover(int *score) {
  MVPRINTW(7, 7, GAMEOVER_MESSAGE);
  MVPRINTW(8, 3, "YOUR SCORE: %05d", *score);
}

void print_win() { MVPRINTW(7, 7, "YOU WIN!!!"); }

void print_screen(GameInfo_t info) {
  if (info.pause == PAUSE_STATE) {
    print_pause();
  } else if (info.pause == START_STATE || info.pause == EXIT_STATE) {
    print_overlay();
  } else if (info.pause == GAMEOVER) {
    print_gameover(&info.score);
    print_overlay();
  } else if (info.pause == WIN_STATE) {
    print_win();
  } else {
    if (info.next)
      printNextfigure(info);
    print_game(info);
    print_stats(info);
  }
}

UserAction_t get_signal() {
  UserAction_t rc = NOISING;
  int user_input = getch();
  if (user_input == '\n')
    rc = START;
  else if (user_input == 'p' || user_input == 'P')
    rc = PAUSE;
  else if (user_input == KEY_END)
    rc = TERMINATE;
  else if (user_input == KEY_LEFT || user_input == 'a' || user_input == 'A') {
    rc = LEFT;
  } else if (user_input == KEY_RIGHT || user_input == 'd' ||
             user_input == 'D') {
    rc = RIGHT;
  } else if (user_input == KEY_DOWN || user_input == 's' || user_input == 'S') {
    rc = DOWN;
  } else if (user_input == KEY_UP || user_input == 'w' || user_input == 'W') {
    rc = UP;
  } else if (user_input == ' ')
    rc = ACTION;

  return rc;
}