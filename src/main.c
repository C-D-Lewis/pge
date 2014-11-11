#include "main.h"

static Window *s_main_window;
static Ship *s_player;

static void logic() {
  GPoint pos = ship_get_position(s_player);
  GRect bounds = ship_get_bounds(s_player);

  // Continuous movement
  if(pge_get_button_state(BUTTON_ID_UP) && pos.x > 0) {
    ship_move(s_player, -SHIP_MOVE_SPEED);
  } else if(pge_get_button_state(BUTTON_ID_DOWN) && pos.x < (144 - bounds.size.w)) {
    ship_move(s_player, SHIP_MOVE_SPEED);
  }
}

static void draw(GContext *ctx) {
  ship_draw(s_player, ctx);
}

static void click(int button_id) {
  switch(button_id) {
    case BUTTON_ID_SELECT:
      // Fire!

      break;
  }
}

static void main_window_load(Window *window) {
  // Create player's Ship
  s_player = ship_create(GPoint(60, 110));

  // Begin game loop
  pge_begin(s_main_window, logic, draw, click);
  pge_set_framerate(25);
}

static void main_window_unload(Window *window) {
  // End game loop
  pge_finish();

  // Destroy the player's Ship
  ship_destroy(s_player);
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
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}