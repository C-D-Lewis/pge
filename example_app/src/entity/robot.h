#include "main.h"

#ifndef ROBOT_H
#define ROBOT_H

#define DIRECTION_UP    0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN  2
#define DIRECTION_LEFT  3

#define SQUARE_SIZE 20
#define SQUARE_SPEED 3

// An extension of PGameEntity with extra logic attributes
typedef struct {
  int direction;
  int pos_x;
  int pos_y;
  bool moving;
} Robot;

Robot* robot_create(int start_x, int start_y);

void robot_destroy(Robot *this);

void robot_set_direction(Robot *this, int new_direction);

void robot_set_is_moving(Robot *this, bool new_state);

void robot_loop(Robot *this);

void robot_render(Robot *this, GContext *ctx);

#endif