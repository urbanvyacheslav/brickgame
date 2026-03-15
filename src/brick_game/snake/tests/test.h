#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#include <gtest/gtest.h>

#include <thread>

#include "../snake_model.h"
namespace s21 {
struct TestSnakeModel : public Snake {
  TestSnakeModel() = default;

  int GetStatusSnakeModel() { return info.pause; }
  void SetStatusSnakeModel(int status) { info.pause = status; }
  void SetApple(int y, int x) {
    apple_in_game.set_y(y);
    apple_in_game.set_x(x);
  }
  void SetTime(double x) { time_ = x; }
  double GetTime() { return time_; }
  vector<Point> GetSnakeModel() { return body; }
  void SetHighScore(int newScore) { info.high_score = newScore; }
};
} // namespace s21
void FreeTestMem(int **matrix, int size);
#endif