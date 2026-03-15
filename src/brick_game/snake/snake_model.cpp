#include "snake_model.h"

bool Point::operator==(const Point other) {
  return (other.x == x && other.y == y);
}
bool Point::operator!=(const Point other) {
  return (other.x != x || other.y != y);
}
bool Point::is_no_correct() { return (x < 0 || x > 19 || y < 0 || y > 9); }

void Snake::snake_create() {
  body = {{4, 1}, {5, 1}, {6, 1}, {7, 1}};
  dir = LEFT_DIR;
  info.pause = START;
  info.field = field_create();
  info.next = nullptr;
  info.level = 1;
  info.score = 0;
  LoadStat();
  snake_speed = SNAKE_START_TIME_LEVEL;
  set_apple_in_game();
}

void field_clear(int **field) {
  for (int i = 0; i < 20; ++i) {
    delete[] field[i];
  }
  delete[] field;
}
int **field_create() {
  int **field = new int *[20];
  for (int i = 0; i < 20; ++i) {
    field[i] = new int[10]();
  }
  return field;
}

void Snake::LoadStat() {
  std::ifstream ifs("brick_game/snake/high_score.txt");
  if (ifs.is_open()) {
    if (!(ifs >> info.high_score))
      info.high_score = 0;
  } else
    info.high_score = 0;
  ifs.close();
}
void Snake::SaveStat() {
  std::ofstream ofs("brick_game/snake/high_score.txt", ios::out);
  ofs << info.high_score;
  ofs.close();
}

void Snake::set_apple_in_game() {
  srand(time(NULL));
  GameInfo_t info_temp = updateCurrentState();
  vector<ApplePoint> searching_new_apple;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (!info_temp.field[i][j]) {
        searching_new_apple.push_back(ApplePoint(j, i));
      }
    }
  }
  ApplePoint new_apple =
      searching_new_apple[rand() % searching_new_apple.size()];
  apple_in_game.set_x(new_apple.get_x());
  apple_in_game.set_y(new_apple.get_y());
}

void Snake::change_state() {
  for (int i = body.size() - 1; i > 0; --i) {
    body[i] = body[i - 1];
  }
}
bool Snake::Move_Left() {
  if (dir == RIGHT_DIR)
    return false;
  change_state();
  int y = body[0].get_y();
  body[0].set_y(--y);
  dir = LEFT_DIR;
  return true;
}

bool Snake::Move_Right() {
  if (dir == LEFT_DIR)
    return false;
  change_state();
  int y = body[0].get_y();
  body[0].set_y(++y);
  dir = RIGHT_DIR;
  return true;
}
bool Snake::Move_Up() {
  if (dir == DOWN_DIR)
    return false;
  change_state();
  int x = body[0].get_x();
  body[0].set_x(--x);
  dir = UP_DIR;
  return true;
}
bool Snake::Move_Down() {
  if (dir == UP_DIR)
    return false;
  change_state();
  int x = body[0].get_x();
  body[0].set_x(++x);
  dir = DOWN_DIR;
  return true;
}
void Snake::Shift_Snake() {
  switch (dir) {
  case LEFT_DIR:
    Move_Left();
    break;
  case RIGHT_DIR:
    Move_Right();
    break;
  case UP_DIR:
    Move_Up();
    break;
  case DOWN_DIR:
    Move_Down();
    break;
  }
}

void Snake::check_snake() {
  if (body[0].is_no_correct()) {
    info.pause = GAMEOVER;
  } else if (is_attachment(apple_in_game) == EATING) {
    info.pause = SPAWN;
  } else if (is_attachment(apple_in_game) == ATTACHMENT_APPLE) {
    info.pause = ATTACHMENT;
  }
  for (size_t i = 1; i < body.size(); i++) {
    if (body[0] == body[i])
      info.pause = GAMEOVER;
  }
}

void Snake::time_is_null() { time_ = 0; }
double Snake::time_calcul() {
  clock_t start = clock();
  clock_t end = clock();
  time_ += ((double)(end - start)) / CLOCKS_PER_SEC;
  return time_;
}

void Snake::userInput(UserAction_t sig, bool hold) {
  if (hold == 1)
    return;
  switch (info.pause) {
  case START:
    on_start_state(sig);
    break;
  case MOVING:
    on_moving_state(sig);
    break;
  case PAUSE:
    on_pause_state(sig);
    break;
  case GAMEOVER:
    on_gameover_state(sig);
    break;
  case ATTACHMENT:
    on_attachment_state();
    break;
  case SPAWN:
    on_spawn_apple_state();
    break;
  case EXIT_STATE:
    on_exit_state();
    break;
  case WIN_STATE:
    on_win_state(sig);
  default:
    break;
  }
}

void Snake::on_start_state(UserAction_t sig) {
  if (sig == START) {
    info.pause = MOVING;
  } else if (sig == TERMINATE)
    info.pause = EXIT_STATE;
}
void Snake::on_moving_state(UserAction_t sig) {
  switch (sig) {
  case TERMINATE:
    info.pause = EXIT_STATE;
    break;
  case LEFT:
    if (Move_Left())
      time_is_null();
    break;
  case RIGHT:
    if (Move_Right())
      time_is_null();
    break;
  case UP:
    if (Move_Up())
      time_is_null();
    break;
  case DOWN:
    if (Move_Down())
      time_is_null();
    break;
  case PAUSE:
    info.pause = PAUSE;
    break;
  case ACTION:
    Shift_Snake();
    time_is_null();
    break;
  case NOISING:
    if (time_calcul() > snake_speed) {
      Shift_Snake();
      time_is_null();
    }
  default:
    break;
  }
  check_snake();
}

void Snake::on_pause_state(UserAction_t sig) {
  if (sig == START) {
    info.pause = MOVING;
  } else if (sig == TERMINATE) {
    info.pause = MOVING;
  }
}

void Snake::on_gameover_state(UserAction_t sig) {
  if (info.high_score < info.score) {
    info.high_score = info.score;
    SaveStat();
  }
  if (sig == START) {
    body.clear();
    apples_eating.clear();
    field_clear(info.field);
    snake_create();
    info.pause = MOVING;
  } else if (sig == TERMINATE) {
    info.pause = EXIT_STATE;
  }
}

void Snake::on_win_state(UserAction_t sig) {
  if (sig == TERMINATE) {
    info.pause = EXIT_STATE;
  }
}

void Snake::on_attachment_state() {
  body.push_back(apples_eating.front());
  if (body.size() == 200) {
    info.pause = WIN_STATE;
    return;
  }
  apples_eating.pop_front();
  info.pause = MOVING;
}

void Snake::on_spawn_apple_state() {
  apples_eating.push_back(apple_in_game);
  info.score++;

  if (info.level < 10 && info.score % 5 == 0) {
    snake_speed -= SNAKE_CHANGE_TIME_LEVEL;
    info.level++;
  }
  set_apple_in_game();
  info.pause = MOVING;
}

void Snake::on_exit_state() { info.pause = EXIT_STATE; }

Attachment_State Snake::is_attachment(const Point &point) {
  return (body[0] == point) ? EATING
         : (body[body.size() - 1] == apples_eating.front() &&
            apples_eating.size())
             ? ATTACHMENT_APPLE
             : NOTHING;
}

GameInfo_t Snake::updateCurrentState() {
  if (info.pause == GAMEOVER)
    return info;
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 10; ++j) {
      info.field[i][j] = 0;
    }
  }

  for (size_t i = 0; i < body.size(); ++i) {
    if (!body[i].is_no_correct()) {
      info.field[body[i].get_x()][body[i].get_y()] = 1;
    }
  }
  info.field[apple_in_game.get_x()][apple_in_game.get_y()] = 2;

  return info;
}
