#include "main.h"

static Window *s_main_window;
static Ship *s_player;

static Shot *shot_arr[MAX_OBJECTS];
static Rock *rock_arr[MAX_OBJECTS];

static void fire() {
  GPoint pos = ship_get_position(s_player);
  GRect bounds = ship_get_bounds(s_player);

  // Adjust
  pos.x += bounds.size.w / 2;

  // Find slot
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(!shot_arr[i]) {
      shot_arr[i] = shot_create(pos);
      return;
    }
  }
}

static void spawn_rock() {
  GPoint pos = GPoint(rand() % 144, -20);

  // Find slot
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(!rock_arr[i]) {
      rock_arr[i] = rock_create(pos);
      return;
    }
  }
}

static void logic() {
  GPoint pos = ship_get_position(s_player);
  GRect bounds = ship_get_bounds(s_player);

  // Continuous movement
  if(pge_get_button_state(BUTTON_ID_UP) && pos.x > 0) {
    ship_move(s_player, -SHIP_MOVE_SPEED);
  } else if(pge_get_button_state(BUTTON_ID_DOWN) && pos.x < (144 - bounds.size.w)) {
    ship_move(s_player, SHIP_MOVE_SPEED);
  }

  // Move shots
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(shot_arr[i]) {
      shot_logic(shot_arr[i]);

      // Out of bounds?
      if(shot_get_position(shot_arr[i]).y < 0) {
        shot_destroy(shot_arr[i]);
        shot_arr[i] = NULL;
      }
    }
  }

  // Move rocks
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(rock_arr[i]) {
      rock_logic(rock_arr[i]);

      // Out of bounds of bottom of screen?
      if(rock_get_position(rock_arr[i]).y > 168) {
        rock_destroy(rock_arr[i]);
        rock_arr[i] = NULL;
      }
    }
  }

  // Do shot collision with enemies

}

static void draw(GContext *ctx) {
  ship_draw(s_player, ctx);

  // Draw any active shots
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(shot_arr[i]) {
      shot_draw(shot_arr[i], ctx);
    }
  }

  // Draw any active rocks
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(rock_arr[i]) {
      rock_draw(rock_arr[i], ctx);
    }
  }
}

static void click(int button_id) {
  switch(button_id) {
    case BUTTON_ID_SELECT:
      // Fire! Shots will self destroy
      fire();
      break;
  }
}

static void main_window_load(Window *window) {
  // Create player's Ship
  s_player = ship_create(GPoint(60, 130));

  // Begin game loop
  pge_begin(s_main_window, logic, draw, click);
  pge_set_framerate(25);
}

static void main_window_unload(Window *window) {
  // End game loop
  pge_finish();

  //Free Shots and Rocks
  for(int i = 0; i < MAX_OBJECTS; i++) {
    if(shot_arr[i]) {
      shot_destroy(shot_arr[i]);
    }
    if(rock_arr[i]) {
      rock_destroy(rock_arr[i]);
    }
  }

  // Destroy the player's Ship
  ship_destroy(s_player);
}

static void timer_handler(void *context) {
  spawn_rock();

  // Continue loop
  app_timer_register(rand() % MAX_SPAWN_INTERVAL, timer_handler, NULL);
}

static void init() {
  s_main_window = window_create();
  window_set_fullscreen(s_main_window, true);
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);

  // Begin spawn loop
  app_timer_register(rand() % MAX_SPAWN_INTERVAL, timer_handler, NULL);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}