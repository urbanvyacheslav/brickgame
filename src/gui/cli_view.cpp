#include "cli_view.h"

s21::CliView::CliView() { cli_controller_ = new s21::GameController(); }

s21::CliView::~CliView() { delete cli_controller_; }

void s21::CliView::startGameEvent() {
  WIN_INIT();
  setlocale(LC_ALL, "");
  print_overlay();
  game_choice();
  endwin();
}

void s21::CliView::game_choice() {
  int menu_point = 0;
  print_menu(0);
  while (1) {
    int input = GET_USER_INPUT;
    if (input == ESC_KEY)
      return;
    else if (input == ENTER_KEY) {
      clear();
      cli_controller_->setGame(menu_point);
      game_loop();
      clear();
      print_overlay();
    } else if (input == KEY_UP)
      menu_point = (menu_point - 1 + 2) % 2;
    else if (input == KEY_DOWN)
      menu_point = (menu_point + 1 + 2) % 2;
    print_menu(menu_point);
  }
}

void s21::CliView::game_loop() {
  if (!cli_controller_)
    return;

  while (1) {
    GameInfo_t game = cli_controller_->play(get_signal());
    if (game.pause == EXIT_STATE) {
      break;
    }
    print_screen(game);
  }
}

void s21::CliView::print_menu(int row) {
  MVPRINTW(BOARD_N / 2, (BOARD_M - BANNER_LEN) / 2 + 1, "%s",
           "       TETRIS       ");
  MVPRINTW(BOARD_N / 2 + 1, (BOARD_M - BANNER_LEN) / 2 + 1, "%s",
           "       SNAKE        ");
  MVPRINTW(BOARD_N / 2 + row, (0) / 2 + 1, "   >>>>");
  MVPRINTW(BOARD_N / 2 + row, (26) / 2 + 1, "<<<<   ");
}