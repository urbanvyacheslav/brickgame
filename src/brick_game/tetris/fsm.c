#include "fsm.h"

#include <ncurses.h>
#include <time.h>
static params_t prms;
void InitGame() {
  prms.info.field = InitField(FIELD_WIDTH, FIELD_HEIGHT + 1);
  prms.block.size = FIGURE_SIZE;
  prms.nextblock.size = FIGURE_SIZE;
  prms.info.score = 0;
  prms.info.level = 1;
  prms.info.pause = START_STATE;
  prms.block.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  prms.nextblock.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
  CreateBlock(&prms.block, RAND_NUMBER);
  CreateBlock(&prms.nextblock, RAND_NUMBER);
  prms.time.level_time = TETRIS_START_TIME_LEVEL;
}
typedef void (*useraction)(params_t *prms);
static params_t prms;
useraction fsm_table[8][9] = {
    {shifting, NULL, exitstate, NULL, NULL, NULL, NULL, NULL, NULL},
    {shifting, NULL, exitstate, NULL, NULL, NULL, NULL, NULL},
    {NULL, pause, exitstate, NULL, NULL, NULL, spawn, spawn, spawn},
    {shifting, pause, exitstate, moveleft, moveright, NULL, movedown, rotate,
     shifting},
    {shifting, pause, exitstate, shifting, shifting, shifting, shifting,
     shifting, shifting},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {shifting, NULL, exitstate, NULL, NULL, NULL, NULL, NULL, gameover},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}};

params_t *data() { return &prms; }

void userInput(UserAction_t action, int hold) {
  if (hold == 1)
    return;
  if (prms.info.pause == EXIT_STATE) {
    prms.info.pause = START_STATE;
    RemoveGame();
    return;
  }
  prms.time.start = clock();
  if ((prms.info.pause == START_STATE) && action == START) {
    InitGame();
  }

  if (prms.info.pause == START_STATE) {
    LoadStat(&prms.info);
  } else {
    updateCurrentState_2();
  }

  prms.rand_number = RAND_NUMBER;
  useraction act = fsm_table[(int)prms.info.pause][action];
  if (act)
    act(&prms);
}

void pause() { prms.info.pause = PAUSE_STATE; }

void spawn() {
  attachment(prms.block, &prms.info);
  if (prms.info.pause != START_STATE)
    prms.info.score += checkTetris(&prms.info);
  newLevel(prms.info.score, &prms.info.level, &prms.time.level_time);
  CopyBlock(&prms.block, &prms.nextblock);
  CreateBlock(&prms.nextblock, prms.rand_number);
  if (collision(prms.block, &prms.info) ||
      GameOverCollision(prms.block, &prms.info)) {
    moveup();
    prms.info.pause = GAMEOVER;
  } else {
    prms.info.pause = MOVING;
  }
  keypad(stdscr, TRUE);
}

void movedown() {
  (prms.block.y_pos) += 1;
  if (collision(prms.block, &prms.info) ||
      GameOverCollision(prms.block, &prms.info)) {
    moveup();
    keypad(stdscr, FALSE);
    prms.info.pause = SPAWN;
  }
}
void moveright() {
  (prms.block.x_pos) += 1;
  if (collision(prms.block, &prms.info)) {
    moveleft();
  }
}

void moveleft() {
  (prms.block.x_pos) -= 1;
  if (collision(prms.block, &prms.info)) {
    moveright();
  }
}

void moveup() { (prms.block.y_pos) -= 1; }

void shifting() {
  time_calcul(prms.time.end, &prms.time.cpu_time_used, prms.time.start);
  if (prms.time.cpu_time_used >= prms.time.level_time &&
      prms.info.pause != PAUSE_STATE) {
    movedown();
    prms.time.cpu_time_used = 0;
  }

  if (prms.info.pause != SPAWN && prms.info.pause != GAMEOVER)
    prms.info.pause = MOVING;
}

void rotate() {
  if (prms.block.type != CUBE_TYPE) {
    Figure_t rotFig;
    rotFig.block = InitField(FIGURE_SIZE, FIGURE_SIZE);
    rotFig.x_pos = prms.block.x_pos;
    rotFig.y_pos = prms.block.y_pos;
    rotFig.size = prms.block.size;
    rotFig.type = prms.block.type;

    rotFigure(&rotFig, &prms.block);

    if (checkStick(rotFig, prms.block, &prms.info)) {
      prms.info.pause = MOVING;
    }
    if (!checkRotate(rotFig, &prms.info)) {
      FigureTakeNul(prms.block.block, FIGURE_SIZE, FIGURE_SIZE);
      CopyBlock(&prms.block, &rotFig);
      prms.info.pause = SHIFTING;
    } else {
      prms.info.pause = SHIFTING;
      movedown(prms);
      keypad(stdscr, FALSE);
    }
    RemoveField(rotFig.block, FIGURE_SIZE);
    rotFig.block = NULL;
  }
}

void gameover() {
  if (prms.info.score > prms.info.high_score) {
    prms.info.high_score = prms.info.score;
    SaveStat(&prms.info);
  }
  prms.info.score = 0;
  prms.info.level = 1;
  prms.info.pause = START_STATE;
  RemoveGame();
}
void exitstate() {
  if (prms.info.pause == PAUSE_STATE) {
    RemoveGame();
  }
  prms.info.pause = EXIT_STATE;
}

GameInfo_t updateCurrentState() {
  GameInfo_t info = {prms.info.field, prms.nextblock.block,
                     prms.info.score, prms.info.high_score,
                     prms.info.level, prms.info.speed,
                     prms.info.pause};

  if (info.pause == START_STATE || info.field == NULL ||
      info.pause == EXIT_STATE) {
    return info;
  }
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      info.field[i][j] = prms.info.field[i][j];
      int x = j - prms.block.x_pos;
      int y = i - prms.block.y_pos;
      if (x >= 0 && x < prms.block.size && y >= 0 && y < prms.block.size) {
        if (prms.block.block[y][x] != 0)
          prms.info.field[i][j] = 2;
      }
    }
  }
  return info;
}

void updateCurrentState_2() {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (prms.info.field[i][j] == 2)
        prms.info.field[i][j] = 0;
    }
  }
}

void RemoveGame() {
  RemoveField(prms.info.field, FIELD_HEIGHT + 1);
  RemoveField(prms.block.block, FIGURE_SIZE);
  RemoveField(prms.nextblock.block, FIGURE_SIZE);
  prms.info.field = NULL;
  prms.block.block = NULL;
  prms.nextblock.block = NULL;
}

int **InitField(int width, int hight) {
  int **field = calloc(hight, sizeof(int *));
  if (field) {
    for (int i = 0; i < hight; i++) {
      field[i] = calloc(width, sizeof(int));
      if (!field[i]) {
        for (int j = 0; j < i; j++) {
          free(field[j]);
        }
        abort();
      }
    }
  } else {
    abort();
  }

  return field;
}

void CopyBlock(Figure_t *figure, Figure_t *newfigure) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      figure->block[i][j] = 0;
      figure->block[i][j] = newfigure->block[i][j];
    }
  }
  figure->x_pos = newfigure->x_pos;
  figure->y_pos = newfigure->y_pos;
  figure->size = newfigure->size;
  figure->type = newfigure->type;
}

void RemoveField(int **field, int hight) {
  if (!field)
    return;
  for (int i = 0; i < hight; i++) {
    free(field[i]);
  }
  free(field);
}

int fewLine(int i, const GameInfo_t *info) {
  int res = 1;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    if (info->field[i][j] == 0)
      res = 0;
  };
  return res;
}

void dropLineTet(int i, GameInfo_t *info) {
  if (i == 0) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      info->field[i][j] = 0;
    }
  } else {
    for (int k = i; k > 0; k--) {
      for (int j = 0; j < FIELD_WIDTH; j++) {
        info->field[k][j] = info->field[k - 1][j];
      };
    };
  };
}

int checkTetris(GameInfo_t *info) {
  int count = 0;
  for (int i = FIELD_HEIGHT; i >= 0; i--) {
    while (fewLine(i, info)) {
      dropLineTet(i, info);
      count++;
    };
  };
  return (count == 1)   ? 100
         : (count == 2) ? 300
         : (count == 3) ? 700
         : (count >= 4) ? 1500
                        : 0;
}

void FigureTakeNul(int **field, int hight, int width) {
  for (int i = 0; i < hight; i++) {
    for (int j = 0; j < width; j++) {
      field[i][j] = 0;
    }
  }
}

void NewFigure(Figure_t *figure, int new_fig[][5]) {
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      figure->block[i][j] = new_fig[i][j];
    }
  }
}

void CreateCube(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 1, 1, 0, 0},
                      {0, 1, 1, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = CUBE_TYPE;
  NewFigure(figure, sample);
}

void CreateFigure1(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0},
                      {0, 1, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = FIGURE_TYPE;
  NewFigure(figure, sample);
}

void CreateFigure2(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 1, 0, 0, 0},
                      {0, 1, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = FIGURE_TYPE;
  NewFigure(figure, sample);
}

void CreateFigure3(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 0, 0, 1, 0},
                      {0, 1, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = FIGURE_TYPE;
  NewFigure(figure, sample);
}

void CreateFigure4(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 0, 1, 1, 0},
                      {0, 1, 1, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = FIGURE_TYPE;
  NewFigure(figure, sample);
}

void CreateFigure5(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 1, 1, 0, 0},
                      {0, 0, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = FIGURE_TYPE;
  NewFigure(figure, sample);
}

void CreateStick(Figure_t *figure) {
  int sample[5][5] = {{0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {1, 1, 1, 1, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
  FigureTakeNul(figure->block, FIGURE_SIZE, FIGURE_SIZE);
  figure->x_pos = START_POSITION_X;
  figure->y_pos = START_POSITION_Y;
  figure->size = FIGURE_SIZE;
  figure->type = STICK_TYPE;
  NewFigure(figure, sample);
}

void CreateBlock(Figure_t *figure, int new_fig) {
  switch ((new_fig)) {
  case 0:
    CreateCube(figure);
    break;
  case 1:
    CreateFigure1(figure);
    break;
  case 2:
    CreateFigure2(figure);
    break;
  case 3:
    CreateFigure3(figure);
    break;
  case 4:
    CreateFigure4(figure);
    break;
  case 5:
    CreateFigure5(figure);
    break;
  case 6:
    CreateStick(figure);
    break;
  default:
    break;
  }
}

int collision(Figure_t figure, GameInfo_t *info) {
  int res = 0;
  int **field = info->field;
  Figure_t tetra = figure;
  for (int i = 0; i < tetra.size; i++) {
    for (int j = 0; j < tetra.size; j++) {
      if (tetra.y_pos >= 0) {
        if (tetra.block[i][j] == 1 &&
            field[i + tetra.y_pos][j + tetra.x_pos] == 1)
          res = 1;
      }
      if (tetra.block[i][j] == 1) {
        if ((tetra.x_pos + j < 0 || tetra.x_pos + j > FIELD_WIDTH - 1 ||
             tetra.y_pos + i > FIELD_HEIGHT - 1))
          res = 1;
      }
    };
  };
  return res;
}

void SaveStat(const GameInfo_t *info) {
  FILE *fp = fopen("brick_game/tetris/high_score.txt", "w+");
  char buf[20];
  sprintf(buf, "%d", info->high_score);
  if (fp != NULL) {
    fputs(buf, fp);
    fclose(fp);
  }
}

void LoadStat(GameInfo_t *info) {
  FILE *fp = fopen("brick_game/tetris/high_score.txt", "r");
  if (fp) {
    if (fscanf(fp, "%d", &info->high_score) == 1)
      ;
    else
      info->high_score = 0;
    fclose(fp);
  }
}

int checkStick(Figure_t figure, Figure_t old_figure, const GameInfo_t *info) {
  int res = 0;
  if (figure.x_pos == -1 && old_figure.type == STICK_TYPE &&
      info->field[figure.y_pos + 5][figure.x_pos + 1] != 1) {
    keypad(stdscr, TRUE);
    res = 1;
    refresh();
  }
  return res;
}

void attachment(Figure_t figure, GameInfo_t *info) {
  for (int i = 0; i < figure.size; i++) {
    for (int j = 0; j < figure.size; j++) {
      if (figure.block[i][j] == 1) {
        int fx = figure.x_pos + j;
        int fy = figure.y_pos + i;
        if (fx >= 0 && fy >= 0) {
          if (info->field[fy][fx] != 1)
            info->field[fy][fx] = figure.block[i][j];
        }
      };
    };
  };
}

int GameOverCollision(Figure_t figure, const GameInfo_t *info) {
  int res = 0;
  if (figure.type == STICK_TYPE) {
    if ((info->field[1][3] == 1) || (info->field[1][4] == 1) ||
        (info->field[1][5] == 1) || (info->field[1][6] == 1) ||
        (info->field[1][7] == 1))
      res = 1;
  }
  for (int i = 0; i < FIGURE_SIZE; i++) {
    if ((info->field[0][3] == 1 && figure.block[i][0] == 1) ||
        (info->field[0][4] == 1 && figure.block[i][1] == 1) ||
        (info->field[0][5] == 1 && figure.block[i][2] == 1) ||
        (info->field[0][6] == 1 && figure.block[i][3] == 1) ||
        (info->field[0][7] == 1 && figure.block[i][4] == 1))
      res = 1;
  }

  return res;
}

void newLevel(int score, int *level, double *level_time) {
  int res = 0;
  for (int i = 1, temp_score = 0; i <= MAX_LEVEL; i++, temp_score += 600) {
    if (score >= temp_score)
      res = i;
  }

  if (*level < res) {
    *level_time -= TETRIS_CHANGE_TIME_LEVEL * (res - *level);
    *level = res;
  }
}

int checkRotate(Figure_t figure, GameInfo_t *info) {
  int res = 0;
  if (collision(figure, info)) {
    res = 1;
  }
  return res;
}

void rotFigure(Figure_t *rotFig, Figure_t *block) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (block->type == STICK_TYPE)
        rotFig->block[j][i] = block->block[i][j];
      else
        rotFig->block[j][i] = block->block[FIGURE_SIZE - i - 1][j];
      if (rotFig->x_pos + i < 0 && rotFig->block[j][i] == 1)
        rotFig->x_pos++;
      else if (rotFig->x_pos + i > FIELD_WIDTH - 1 && rotFig->block[j][i] == 1)
        rotFig->x_pos--;
      else if (rotFig->y_pos + j > FIELD_HEIGHT - 1 && rotFig->block[j][i] == 1)
        rotFig->y_pos--;
    };
  };
}

void time_calcul(clock_t end, double *cpu_time_used, clock_t start) {
  end = clock();
  *cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
}