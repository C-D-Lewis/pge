#include "robot.h"

static void logic(Robot *this) {
  GPoint pos = pge_sprite_get_position(this->sprite);

  // Move square and wrap to screen
  if(this->moving) {
    switch(this->direction) {
      case DIRECTION_UP:
        pos.y -= SQUARE_SPEED;
        if(pos.y < -SQUARE_SIZE) {
          pos.y = 168;
        }
        break;

      case DIRECTION_RIGHT:
        pos.x += SQUARE_SPEED;
        if(pos.x > 144 + SQUARE_SIZE) {
          pos.x = -SQUARE_SIZE;
        }
        break;

      case DIRECTION_DOWN:
        pos.y += SQUARE_SPEED;
        if(pos.y > 168 + SQUARE_SIZE) {
          pos.y = -SQUARE_SIZE;
        }
        break;

      case DIRECTION_LEFT:
        pos.x -= SQUARE_SPEED;
        if(pos.x < -SQUARE_SIZE) {
          pos.x = 144;
        }
        break;
    }

    // Update sprite
    pge_sprite_set_position(this->sprite, pos);
  }
}

static void render(Robot *this, GContext *ctx) {
  pge_sprite_draw(this->sprite, ctx);
}

Robot* robot_create(GPoint start_position) {
  Robot *this = malloc(sizeof(Robot));
  this->direction = DIRECTION_UP;

  this->sprite = pge_sprite_create(start_position, RESOURCE_ID_ROBOT_UP);

  return this;
}

void robot_destroy(Robot *this) {
  pge_sprite_destroy(this->sprite);
  free(this);
}

void robot_set_direction(Robot *this, int new_direction) {
  this->direction = new_direction;

  // Set the sprite bitmap
  switch(this->direction) {
    case DIRECTION_UP:
      pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_UP);
      break;
    case DIRECTION_RIGHT:
      pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_RIGHT);
      break;
    case DIRECTION_DOWN:
      pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_DOWN);
      break;
    case DIRECTION_LEFT:
      pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_LEFT);
      break;
  }
}

void robot_set_is_moving(Robot *this, bool new_state) {
  this->moving = new_state;
}

void robot_logic(Robot *this) {
  logic(this);
}

void robot_render(Robot *this, GContext *ctx) {
  render(this, ctx);
}