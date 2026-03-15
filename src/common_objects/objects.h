#ifndef OBJECTS_H
#define OBJECTS_H

#include <ncurses.h>
#undef border
#include <time.h>

typedef struct {
  int x_pos;
  int y_pos;
  int size;
  int **block;
  int type;
} Figure_t;

typedef struct {
  clock_t start;
  clock_t end;
  double cpu_time_used;
  double level_time;
} time_info;

#endif