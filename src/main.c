#include "main.h"

static Window *s_main_window;

static void logic() {

}

static void draw(GContext *ctx) {

}

static void click(int button_id) {

}

static void main_window_load(Window *window) {
  pge_begin(s_main_window, logic, draw, click);
}

static void main_window_unload(Window *window) {
  pge_finish();
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