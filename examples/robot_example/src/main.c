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
static TextLayer *s_score_layer;
static Robot *s_robot, *s_robot2;

static char s_score_buffer[24];
static int s_direction, s_score;
static bool s_moving;

/******************************** Game ****************************************/

static void loop() {
  robot_logic(s_robot);

  // Destroy robots collided with
  bool collided = pge_check_collision(s_robot->sprite, s_robot2->sprite);
  if(collided) {
    robot_destroy(s_robot2);

    // Process score
    s_score++;
    snprintf(s_score_buffer, sizeof(s_score_buffer), "Score: %d (Best: %d)", s_score, pge_title_get_highscore());
    text_layer_set_text(s_score_layer, s_score_buffer);

    // Create new at random location
    s_robot2 = robot_create(GPoint(rand() % 130, rand() % 140));
  }
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
      s_moving = !s_moving;
      robot_set_is_moving(s_robot, s_moving);
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

/******************************* Main Window **********************************/

static void main_window_load(Window *window) {
  // Create a Robot
  s_robot = robot_create(GPoint(30, 30));
  s_robot2 = robot_create(GPoint(100, 100));

  // Create game canvas and begin render loop
  pge_begin(window, loop, draw, click);

  // Setup score TextLayer
  s_score_layer = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_text_color(s_score_layer, GColorBlack);
  text_layer_set_background_color(s_score_layer, GColorWhite);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_score_layer));

  // Show initial score
  snprintf(s_score_buffer, sizeof(s_score_buffer), "Score: %d (Best: %d)", s_score, pge_title_get_highscore());
  text_layer_set_text(s_score_layer, s_score_buffer);
}

static void main_window_unload(Window *window) {
  // Destroy the Robot
  robot_destroy(s_robot);
  robot_destroy(s_robot2);

  // Score layer
  text_layer_destroy(s_score_layer);

  // Destroy all game resources
  pge_finish();

  // Destroy game Window
  window_destroy(s_main_window);
}

/******************************** Title ***************************************/

static void title_click(int button_id) {
  switch(button_id) {
    // Some other action
    case BUTTON_ID_SELECT:
      
      break;

    case BUTTON_ID_DOWN:
      // Go to game!
      s_main_window = window_create();
      window_set_background_color(s_main_window, GColorBlack);
      window_set_fullscreen(s_main_window, true);
      window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload
      });
      window_stack_push(s_main_window, true);
      break;
  }
}

/******************************** App *****************************************/

static void init(void) {
  pge_title_push("Robot Example Game", "", "PLAY >", GColorWhite, RESOURCE_ID_TITLE_BG, title_click);
}

static void deinit(void) {
  // Save highscore
  if(s_score > pge_title_get_highscore()) {
    pge_title_set_highscore(s_score);
  }

  pge_title_pop();
}

int main(void) {
  // Randomize behavior
  srand(time(NULL));

  init();
  app_event_loop();
  deinit();
}
