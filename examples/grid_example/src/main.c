#include "main.h"

static Window *s_window;
static Robot *s_robot;

static void logic() {

}

static void draw(GContext *ctx) {
  pge_grid_draw_lines(ctx, GColorWhite);

  pge_sprite_draw(s_robot->sprite, ctx);
}

static void click(int button_id) {
  int dir = s_robot->direction;

  switch(button_id) {
    case BUTTON_ID_UP:
      dir--;
      if(dir < DIRECTION_UP) {
        dir = DIRECTION_LEFT;
      }
      break;

    case BUTTON_ID_SELECT:
      {
        GPoint pos = s_robot->sprite->position;

        // Advance
        switch(s_robot->direction) {
          case DIRECTION_UP:
            pos = pge_grid_move(pos, 0, -1);
            break;
          case DIRECTION_RIGHT:
            pos = pge_grid_move(pos, 1, 0);
            break;
          case DIRECTION_DOWN:
            pos = pge_grid_move(pos, 0, 1);
            break;
          case DIRECTION_LEFT:
            pos = pge_grid_move(pos, -1, 0);
          break;
        }

        pge_sprite_set_position(s_robot->sprite, pos);
      }
      break;

    case BUTTON_ID_DOWN:
      dir++;
      if(dir > DIRECTION_LEFT) {
        dir = DIRECTION_UP;
      }
      break;
  }

  // Update the Robot entity
  robot_set_direction(s_robot, dir);
}

static void window_load(Window *window) {
  pge_begin(window, logic, draw, click);

  // No high FPS required
  pge_set_framerate(5);

  s_robot = robot_create(GPoint(0, 0));

  pge_grid_set_tile_size(s_robot->sprite->bitmap->bounds.size.w);
}

static void window_unload(Window *window) {
  pge_finish();
  robot_destroy(s_robot);

  // Finally
  window_destroy(window);
}

static void init(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);
}

static void deinit(void) {

}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
