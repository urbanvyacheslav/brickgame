#include "unit_tests.h"

#include <check.h>

START_TEST(create_block_0) {
  Figure_t figure0;
  Figure_t nextfigure;
  figure0.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure0, 0);
  CreateBlock(&nextfigure, 1);
  ck_assert_int_eq(figure0.block[1][1], 1);
  ck_assert_int_eq(figure0.block[1][2], 1);
  ck_assert_int_eq(figure0.block[2][1], 1);
  ck_assert_int_eq(figure0.block[2][2], 1);

  RemoveField(figure0.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

START_TEST(create_block_1) {
  Figure_t figure1;
  Figure_t nextfigure;
  figure1.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure1, 1);
  CreateBlock(&nextfigure, 2);
  ck_assert_int_eq(figure1.block[1][2], 1);
  ck_assert_int_eq(figure1.block[2][1], 1);
  ck_assert_int_eq(figure1.block[2][2], 1);
  ck_assert_int_eq(figure1.block[2][3], 1);

  RemoveField(figure1.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

START_TEST(create_block_2) {
  Figure_t figure2;
  Figure_t nextfigure;
  figure2.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure2, 2);
  CreateBlock(&nextfigure, 1);

  ck_assert_int_eq(figure2.block[1][1], 1);
  ck_assert_int_eq(figure2.block[2][1], 1);
  ck_assert_int_eq(figure2.block[2][2], 1);
  ck_assert_int_eq(figure2.block[2][3], 1);

  RemoveField(figure2.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

START_TEST(create_block_3) {
  Figure_t figure3;
  Figure_t nextfigure;
  figure3.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure3, 3);
  CreateBlock(&nextfigure, 1);

  ck_assert_int_eq(figure3.block[1][3], 1);
  ck_assert_int_eq(figure3.block[2][1], 1);
  ck_assert_int_eq(figure3.block[2][2], 1);
  ck_assert_int_eq(figure3.block[2][3], 1);

  RemoveField(figure3.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

START_TEST(create_block_4) {
  Figure_t figure4;
  Figure_t nextfigure;
  figure4.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure4, 4);
  CreateBlock(&nextfigure, 1);

  ck_assert_int_eq(figure4.block[1][2], 1);
  ck_assert_int_eq(figure4.block[1][3], 1);
  ck_assert_int_eq(figure4.block[2][1], 1);
  ck_assert_int_eq(figure4.block[2][2], 1);

  RemoveField(figure4.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

START_TEST(create_block_5) {
  Figure_t figure5;
  Figure_t nextfigure;
  figure5.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure5, 5);
  CreateBlock(&nextfigure, 1);

  ck_assert_int_eq(figure5.block[1][1], 1);
  ck_assert_int_eq(figure5.block[1][2], 1);
  ck_assert_int_eq(figure5.block[2][2], 1);
  ck_assert_int_eq(figure5.block[2][3], 1);

  RemoveField(figure5.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

START_TEST(create_block_6) {
  Figure_t figure6;
  Figure_t nextfigure;
  figure6.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  nextfigure.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&figure6, 6);
  CreateBlock(&nextfigure, 1);

  ck_assert_int_eq(figure6.block[2][0], 1);
  ck_assert_int_eq(figure6.block[2][1], 1);
  ck_assert_int_eq(figure6.block[2][2], 1);
  ck_assert_int_eq(figure6.block[2][3], 1);

  RemoveField(figure6.block, FIGURE_SIZE);
  RemoveField(nextfigure.block, FIGURE_SIZE);
}
END_TEST

Suite *create_block(void) {
  Suite *s;
  s = suite_create("\033[44m create_block_tests \033[0m");
  TCase *tc;
  tc = tcase_create("create_block");
  tcase_add_test(tc, create_block_0);
  tcase_add_test(tc, create_block_1);
  tcase_add_test(tc, create_block_2);
  tcase_add_test(tc, create_block_3);
  tcase_add_test(tc, create_block_4);
  tcase_add_test(tc, create_block_5);
  tcase_add_test(tc, create_block_6);
  suite_add_tcase(s, tc);
  return s;
}

int create_block_test(void) {
  Suite *s = create_block();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}

START_TEST(spawn_state) {
  userInput(START, FALSE);
  params_t *Game = data();
  userInput(NOISING, FALSE);
  for (int j = 0; j < FIELD_WIDTH; j++)
    Game->info.field[FIELD_HEIGHT - 1][j] = 1;
  int check_spawn = 0;
  for (int i = 0; i < 22; i++) {
    userInput(DOWN, FALSE);
    if (Game->info.pause == SPAWN)
      check_spawn++;
  }
  ck_assert_int_eq(Game->info.score, 100);
  ck_assert_int_eq(check_spawn, 1);
  ck_assert_int_eq(Game->info.pause, MOVING);
  RemoveGame();
  Game->info.pause = START_STATE;
}
END_TEST

START_TEST(pause_state) {
  userInput(START, FALSE);
  userInput(PAUSE, FALSE);
  params_t *Game = data();
  ck_assert_int_eq(Game->info.pause, PAUSE_STATE);
  RemoveGame();
  Game->info.pause = START_STATE;
}
END_TEST

START_TEST(rotate_state) {
  userInput(START, FALSE);
  params_t *Game = data();
  userInput(NOISING, FALSE);
  userInput(ACTION, FALSE);
  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.field[18][5], 0);
  ck_assert_int_eq(Game->info.pause, SHIFTING);
  RemoveField(Game->info.field, FIELD_HEIGHT + 1);
  RemoveField(Game->block.block, FIGURE_SIZE);
  RemoveField(Game->nextblock.block, FIGURE_SIZE);
  Game->info.pause = START_STATE;
}
END_TEST

START_TEST(gameover_state) {
  userInput(START, FALSE);
  params_t *Game = data();
  userInput(DOWN, FALSE);
  userInput(DOWN, FALSE);
  userInput(DOWN, FALSE);
  userInput(DOWN, FALSE);
  userInput(LEFT, FALSE);
  userInput(RIGHT, FALSE);
  userInput(DOWN, FALSE);
  userInput(DOWN, FALSE);
  for (int j = 0; j < FIELD_WIDTH; j++)
    Game->info.field[0][j] = 1;
  for (int i = 0; i < 18; i++) {
    userInput(DOWN, FALSE);
  }
  ck_assert_int_eq(Game->info.pause, GAMEOVER);
  userInput(NOISING, FALSE);
  userInput(TERMINATE, FALSE);
  ck_assert_int_eq(Game->info.pause, EXIT_STATE);
  Game->info.pause = START_STATE;
}
END_TEST

Suite *tetris_state(void) {
  Suite *s;
  s = suite_create("\033[44m tetris state tests \033[0m");
  TCase *tc;
  tc = tcase_create("tetris_state");
  tcase_add_test(tc, spawn_state);
  tcase_add_test(tc, pause_state);
  tcase_add_test(tc, rotate_state);
  tcase_add_test(tc, gameover_state);
  suite_add_tcase(s, tc);
  return s;
}

int tetris_state_test(void) {
  Suite *s = tetris_state();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);

  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return number_failed;
}

int main() {
  int number_failed = 0;

  number_failed += create_block_test();
  number_failed += tetris_state_test();

  printf("                           ====================\n\n             ");
  if (number_failed > 0) {
    printf("                           \033[41m========= FAILED: %d "
           "=========\033[0m\n         ",
           number_failed);
  } else {
    printf("\033[42m========= PASSED =========\033[0m\n\n");
  }
  printf("====================\n");
  return 0;
}
