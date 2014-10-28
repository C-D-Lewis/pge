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
static Robot *s_robot, *s_robot2;

static int s_direction;
static bool s_moving = true;

/******************************** Game ****************************************/

static void loop() {
  robot_logic(s_robot);

  bool collided = pge_collide(s_robot->sprite, s_robot2->sprite);
  robot_set_is_moving(s_robot, !collided);
}

static void draw(GContext *ctx) {
  robot_render(s_robot, ctx);
  robot_render(s_robot2, ctx);
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
  s_robot = robot_create(GPoint(30, 30));
  s_robot2 = robot_create(GPoint(100, 100));

  // Create game canvas and begin render loop
  pge_begin(window, loop, draw, click);
}

static void main_window_unload(Window *window) {
  // Destroy the Robot
  robot_destroy(s_robot);
  robot_destroy(s_robot2);

  // Destroy all game resources
  pge_finish();
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
