#include "snakecontroller.h"

s21::SnakeController::SnakeController() { model_ = new Snake(); };

s21::SnakeController::~SnakeController() { delete model_; };

GameInfo_t s21::SnakeController::play(UserAction_t act) {
  model_->userInput(act, 0);
  return model_->updateCurrentState();
}

// const char* s21::SnakeController::getRules() const {
//   return (model_) ? model_->getRules() : "";
// }
