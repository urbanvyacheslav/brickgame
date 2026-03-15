#include "test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(SnakeTest, GameOverWall) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), GAMEOVER);
  snakeTest.userInput(START, 0);

  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), MOVING);
}

TEST(SnakeTest, GameOverSnake) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(NOISING, 0);

  snakeTest.SetApple(3, 1);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(RIGHT, 0);
  snakeTest.userInput(UP, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);

  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), GAMEOVER);
}

TEST(SnakeTest, Pause) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(PAUSE, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), PAUSE_STATE);
  snakeTest.userInput(START, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), MOVING);
  snakeTest.userInput(PAUSE, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), PAUSE_STATE);
  snakeTest.userInput(TERMINATE, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), MOVING);
}

TEST(SnakeTest, EXIT) {
  s21::TestSnakeModel snakeTest;
  snakeTest.userInput(TERMINATE, 0);
  snakeTest.userInput(NOISING, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), EXIT_STATE);
}

TEST(SnakeTest, WIN) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.SetStatusSnakeModel(WIN_STATE);
  snakeTest.userInput(NOISING, 0);
  snakeTest.userInput(TERMINATE, 0);
  snakeTest.userInput(NOISING, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), EXIT_STATE);
}

TEST(SnakeTest, AttachApple) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(NOISING, 0);
  snakeTest.SetHighScore(0);
  snakeTest.SetApple(3, 1);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  EXPECT_EQ(snakeTest.GetSnakeModel().size() > 4, true);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  snakeTest.userInput(LEFT, 0);
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), GAMEOVER);
}

TEST(SnakeTest, Time) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.SetTime(0.1);
  snakeTest.userInput(NOISING, 0);
  EXPECT_EQ(snakeTest.GetTime(), 0.0);
}

TEST(SnakeTest, ShiftDown) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.SetTime(0.1);
  snakeTest.userInput(NOISING, 0);
  EXPECT_EQ(snakeTest.GetTime(), 0.0);
}

TEST(SnakeTest, ShiftRight) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(RIGHT, 0);
  snakeTest.SetTime(0.1);
  snakeTest.userInput(NOISING, 0);
  EXPECT_EQ(snakeTest.GetTime(), 0.0);
}

TEST(SnakeTest, ShiftUp) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(DOWN, 0);
  snakeTest.userInput(RIGHT, 0);
  snakeTest.userInput(UP, 0);
  snakeTest.SetTime(0.1);
  snakeTest.userInput(NOISING, 0);
  EXPECT_EQ(snakeTest.GetTime(), 0.0);
}

TEST(SnakeTest, GameInfo) {
  s21::TestSnakeModel snakeTest;
  EXPECT_EQ(snakeTest.GetStatusSnakeModel(), START);
  snakeTest.userInput(START, 0);
  snakeTest.userInput(NOISING, 0);
  GameInfo_t testInfo = snakeTest.updateCurrentState();
  EXPECT_EQ(testInfo.score, 0);
  EXPECT_EQ(testInfo.level, 1);
  EXPECT_EQ(testInfo.next, nullptr);
}