#include "gamecontroller.h"

s21::GameController::~GameController() { delete controller_; }

void s21::GameController::setGame(int game) {
  if (controller_)
    delete controller_;
  switch (game) {
  case 1:
    controller_ = new SnakeController();
    break;
  case 0:
  default:
    controller_ = new TetrisController();
    break;
  }
}

GameInfo_t s21::GameController::play(UserAction_t act) {
  return (!controller_) ? GameInfo_t() : controller_->play(act);
}
