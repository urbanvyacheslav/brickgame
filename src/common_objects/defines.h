#ifndef DEFINES_H
#define DEFINES_H

#define WIN_INIT()                                                             \
  {                                                                            \
    initscr();                                                                 \
    start_color();                                                             \
    noecho();                                                                  \
    curs_set(0);                                                               \
    keypad(stdscr, TRUE);                                                      \
    nodelay(stdscr, TRUE);                                                     \
    scrollok(stdscr, TRUE);                                                    \
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);                                  \
    init_pair(2, COLOR_BLUE, COLOR_BLACK);                                     \
    init_pair(3, COLOR_GREEN, COLOR_BLACK);                                    \
    init_pair(4, COLOR_BLUE, COLOR_BLACK);                                     \
  }

#define GET_USER_INPUT getch()

#define MVPRINTW(y, x, ...)                                                    \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define GAMEOVER_MESSAGE "GAME OVER"
#define INTRO_MESSAGE "Press ENTER to start"
#define ROWS_MAP 21

#define BOARDS_BEGIN 2

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define HUD_WIDTH 17
#define BOARD_N 20
#define BOARD_M 20
#define BANNER_LEN 20

#define START_POSITION_Y -2
#define START_POSITION_X 3
#define FIGURE_SIZE 5
#define FIGURE_TYPE 1
#define STICK_TYPE 2
#define CUBE_TYPE 3
#define CUBE_SIZE 2
#define RAND_NUMBER rand() % 7

#define MAX_LEVEL 10
#define TETRIS_START_TIME_LEVEL 0.02
#define TETRIS_CHANGE_TIME_LEVEL 0.001
#define SNAKE_START_TIME_LEVEL 0.01
#define SNAKE_CHANGE_TIME_LEVEL 0.0007

#define ENTER_KEY 10
#define ESC_KEY 27
#define SPACE ' '
#define NO_INPUT 8

typedef enum {
  START = 0,
  PAUSE,
  TERMINATE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ACTION,
  NOISING
} UserAction_t;

typedef enum {
  START_STATE = 0,
  PAUSE_STATE,
  SPAWN,
  MOVING,
  SHIFTING,
  COLLIDE,
  GAMEOVER,
  EXIT_STATE,
  ATTACHMENT,
  WIN_STATE
} State;

enum Direction { LEFT_DIR = 1, RIGHT_DIR = 2, UP_DIR = 3, DOWN_DIR = 4 };

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif
