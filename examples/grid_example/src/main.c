#include "main.h"

static Window *s_window;
static Robot *s_robot;

static void logic() {

}

static void draw(GContext *ctx) {
  pge_grid_draw_lines(ctx, GColorWhite);

  robot_draw(s_robot);
}

static void click(int button_id) {
  switch(button_id) {
    case BUTTON_ID_UP:
    
      break;
    
    case BUTTON_ID_SELECT:
    
      break;

    case BUTTON_ID_DOWN:

      break;
  }
}

static void window_load(Window *window) {
  pge_begin(window, logic, draw, click);

  // No high FPS required
  pge_set_framerate(5);

  s_robot = robot_create(GPoint(0, 0));
}

static void window_unload(Window *window) {
  pge_finish();
  robot_destroy(s_robot);

  // Finally
  window_destroy(window);
}

static void init(void) {
  s_window = window_create();
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
