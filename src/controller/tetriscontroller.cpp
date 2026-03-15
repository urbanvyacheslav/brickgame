#include "tetriscontroller.h"

GameInfo_t s21::TetrisController::play(UserAction_t act) {
  userInput(act, 0);
  return updateCurrentState();
}