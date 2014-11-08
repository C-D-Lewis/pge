#include "pge.h"

// State
static Window *s_parent;
static Layer *s_canvas;
static AppTimer *s_render_timer;
static BitmapLayer *s_bg_layer;
static GBitmap *s_bg_bitmap;

static PGELogicHandler *s_logic_handler;
static PGERenderHandler *s_render_handler;
static PGEClickHandler *s_click_handler;

static bool s_button_states[3];
static int s_framerate;

// Internal prototypes
static void delta_handler(void *context);
static void canvas_update_proc(Layer *layer, GContext *ctx);
static void stop_rendering();
static void start_rendering();
static void destroy();
static void click_config_provider(void *context);
static int get_delta_from_framerate();

/*********************************** Engine ***********************************/

void pge_begin(Window *parent, PGELogicHandler *logic_handler, PGERenderHandler *render_handler, PGEClickHandler *click_handler) {
  Layer *window_layer = window_get_root_layer(parent);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Allocate
  s_parent = parent;

  // Set up background
  s_bg_layer = bitmap_layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bg_layer));

  // Set up canvas
  s_canvas = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
  layer_set_update_proc(s_canvas, canvas_update_proc);
  layer_add_child(window_layer, s_canvas);
  s_logic_handler = logic_handler;
  s_render_handler = render_handler;

  if(click_handler != NULL) {
    s_click_handler = click_handler;
    window_set_click_config_provider(s_parent, click_config_provider);
  }

  // Init button states (may be redundant)
  for(int i = 0; i < 3; i++) {
    s_button_states[i] = false;
  }

  // Go!
  start_rendering();
}

void pge_finish() {
  // Stop the game
  stop_rendering();
}

bool pge_get_button_state(ButtonId button) {
  switch(button) {
    case BUTTON_ID_UP:
      return s_button_states[0];
    case BUTTON_ID_SELECT:
      return s_button_states[1];
    case BUTTON_ID_DOWN:
      return s_button_states[2];
    default: 
      return false;
  }
}

void pge_set_framerate(int new_rate) {
  s_framerate = new_rate;
}

void pge_set_background(int bg_resource_id) {
  if(s_bg_bitmap) {
    gbitmap_destroy(s_bg_bitmap);
  }
  s_bg_bitmap = gbitmap_create_with_resource(bg_resource_id);
  bitmap_layer_set_bitmap(s_bg_layer, s_bg_bitmap);
}

/************************* Engine Internal Functions **************************/

static int get_delta_from_framerate() {
  return 1000 / s_framerate;
}

static void delta_handler(void *context) {
  if(s_logic_handler != NULL && s_render_handler != NULL) {
    // Do this frame
    layer_mark_dirty(s_canvas);
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Loop or Render handler not set!");
  }
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  // Render and logic
  if(s_logic_handler != NULL && s_render_handler != NULL) {
    s_render_handler(ctx);
    s_logic_handler();

    // Next frame
    s_render_timer = app_timer_register(get_delta_from_framerate(), delta_handler, NULL);
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Loop or Render handler not set!");
  }
}

static void stop_rendering() {
  if(s_render_timer != NULL) {
    // Cancel any Timer
    app_timer_cancel(s_render_timer);
    s_render_timer = NULL;

    destroy();
  }
}

static void start_rendering() {
  // Stop any current Timer
  stop_rendering();

  // Register new Timer to begin frame rendering loop
  s_render_timer = app_timer_register(get_delta_from_framerate(), delta_handler, NULL);
}

static void destroy() {
  // Destroy canvas
  layer_destroy(s_canvas);
  bitmap_layer_destroy(s_bg_layer);
  gbitmap_destroy(s_bg_bitmap);
}

static void up_pressed_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_button_states[0] = true;
}

static void up_released_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_button_states[0] = false;
}

static void select_pressed_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_button_states[1] = true;
}

static void select_released_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_button_states[1] = false;
}

static void down_pressed_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_button_states[2] = true;
}

static void down_released_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_button_states[2] = false;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_click_handler(BUTTON_ID_SELECT);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_click_handler(BUTTON_ID_UP);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_click_handler(BUTTON_ID_DOWN);
}

static void click_config_provider(void *context) {
  window_raw_click_subscribe(BUTTON_ID_UP, up_pressed_click_handler, up_released_click_handler, NULL);
  window_raw_click_subscribe(BUTTON_ID_SELECT, select_pressed_click_handler, select_released_click_handler, NULL);
  window_raw_click_subscribe(BUTTON_ID_DOWN, down_pressed_click_handler, down_released_click_handler, NULL);

  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}