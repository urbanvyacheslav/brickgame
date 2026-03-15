#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include "../controller/gamecontroller.h"
extern "C" {
#include "frontend.h"
}

namespace s21 {
class CliView {
public:
  CliView();
  CliView(const CliView &) = delete;
  CliView &operator=(const CliView &) = delete;
  ~CliView();

  void startGameEvent();

private:
  GameController *cli_controller_;

  void print_menu(int row);
  void game_loop();
  void game_choice();
};
} // namespace s21

#endif