#include "robot.h"

static void loop(Robot *this) {
  // Move square and wrap to screen
  if(this->moving) {
    switch(this->direction) {
      case DIRECTION_UP:
        this->pos_y -= SQUARE_SPEED;
        if(this->pos_y < -SQUARE_SIZE) {
          this->pos_y = 168;
        }
        break;

      case DIRECTION_RIGHT:
        this->pos_x += SQUARE_SPEED;
        if(this->pos_x > 144 + SQUARE_SIZE) {
          this->pos_x = -SQUARE_SIZE;
        }
        break;

      case DIRECTION_DOWN:
        this->pos_y += SQUARE_SPEED;
        if(this->pos_y > 168 + SQUARE_SIZE) {
          this->pos_y = -SQUARE_SIZE;
        }
        break;

      case DIRECTION_LEFT:
        this->pos_x -= SQUARE_SPEED;
        if(this->pos_x < -SQUARE_SIZE) {
          this->pos_x = 144;
        }
        break;
    }
  }
}

static void render(Robot *this, GContext *ctx) {
  // Draw square
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(this->pos_x, this->pos_y, SQUARE_SIZE, SQUARE_SIZE), 0, GCornerNone);

  // Show direction
  graphics_context_set_fill_color(ctx, GColorBlack);
  switch(this->direction) {
    case DIRECTION_UP:
        graphics_fill_rect(ctx, GRect(this->pos_x + 2, this->pos_y + 2, SQUARE_SIZE - 4, 2), 0, GCornerNone);
        break;

      case DIRECTION_RIGHT:
        graphics_fill_rect(ctx, GRect(this->pos_x + SQUARE_SIZE - 4, this->pos_y + 2, 2, SQUARE_SIZE - 4), 0, GCornerNone);
        break;

      case DIRECTION_DOWN:
        graphics_fill_rect(ctx, GRect(this->pos_x + 2, this->pos_y + SQUARE_SIZE - 4, SQUARE_SIZE - 4, 2), 0, GCornerNone);
        break;

      case DIRECTION_LEFT:
        graphics_fill_rect(ctx, GRect(this->pos_x + 2, this->pos_y + 2, 2, SQUARE_SIZE - 4), 0, GCornerNone);
        break;
  }
}

Robot *robot_create(int start_x, int start_y) {
  Robot *this = malloc(sizeof(Robot));
  this->direction = DIRECTION_UP;
  this->pos_x = start_x;
  this->pos_y = start_y;

  return this;
}

void robot_destroy(Robot *this) {
  free(this);
}

void robot_set_direction(Robot *this, int new_direction) {
  this->direction = new_direction;
}

void robot_set_is_moving(Robot *this, bool new_state) {
  this->moving = new_state;
}

void robot_loop(Robot *this) {
  loop(this);
}

void robot_render(Robot *this, GContext *ctx) {
  render(this, ctx);
}