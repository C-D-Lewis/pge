/**
 * PGE Example App - simple robot
 * https://github.com/C-D-Lewis/pge
 *
 * Author:
 * Chris Lewis
 *
 * Use select to toggle moving the robot
 * Use up and down to rotate the movement direction
 */

#include "main.h"

static Window *s_main_window;
static PGE *s_game;
static Robot *s_robot;

static int s_direction;
static bool s_moving;

/******************************** Game ****************************************/

static void loop() {
  robot_loop(s_robot);

  if(pge_get_button_state(s_game, BUTTON_ID_SELECT)) {
    s_moving = false;
  } else {
    s_moving = true;
  }
  robot_set_is_moving(s_robot, s_moving);
}

static void draw(GContext *ctx) {
  robot_render(s_robot, ctx);
}

static void click(int button_id) {
  // Change direction - clockwise 0 - 3
  switch(button_id) {
    case BUTTON_ID_UP:
      s_direction--;
      if(s_direction < DIRECTION_UP) {
        s_direction = DIRECTION_LEFT;
      }
      break;

    case BUTTON_ID_SELECT:
      // s_moving = !s_moving;
      break;

    case BUTTON_ID_DOWN:
      s_direction++;
      if(s_direction > DIRECTION_LEFT) {
        s_direction = DIRECTION_UP;
      }
      break;
  }

  // Update the Robot entity
  robot_set_direction(s_robot, s_direction);
}

/******************************** App *****************************************/

static void main_window_load(Window *window) {
  // Create a Robot
  s_robot = robot_create(0, 0);

  // Create game canvas and begin render loop
  s_game = pge_begin(window, loop, draw, click);
}

static void main_window_unload(Window *window) {
  // Destroy the Robot
  robot_destroy(s_robot);

  // Destroy all game resources
  pge_finish(s_game);
}

static void init(void) {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  window_set_fullscreen(s_main_window, true);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);
}

static void deinit(void) {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
