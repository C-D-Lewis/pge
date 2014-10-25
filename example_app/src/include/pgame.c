#include "pgame.h"

// Internal prototypes
static void delta_handler(void *context);
static void canvas_update_proc(Layer *layer, GContext *ctx);
static void stop_rendering(PGame *this);
static void start_rendering(PGame *this);
static void destroy(PGame *this);
static void click_config_provider(void *context);

PGame* pgame_begin(Window *parent, PGameLogicHandler *logic_handler, PGameRenderHandler *render_handler, PGameClickHandler *click_handler) {
  PGame *this = malloc(sizeof(PGame));

  // Allocate
  this->parent = parent;
  this->canvas = layer_create_with_data(GRect(0, 0, 144, 168), sizeof(uint8_t));

  // Set up
  this->is_running = true; // Required for first draw
  layer_set_update_proc(this->canvas, canvas_update_proc);
  layer_add_child(window_get_root_layer(this->parent), this->canvas);
  this->logic_handler = logic_handler;
  this->render_handler = render_handler;

  if(click_handler != NULL) {
    this->click_handler = click_handler;
    window_set_click_config_provider_with_context(this->parent, click_config_provider, this);
  }

  // Hack to get ref of this into LayerUpdateProc
  void *ptr = layer_get_data(this->canvas);
  *((PGame*)ptr) = *(this);

  // Go!
  start_rendering(this);
  return this;
}

void pgame_finish(PGame *this) {
  // Stop the game
  stop_rendering(this);
}

/**************************** Internal Functions ******************************/

static void delta_handler(void *context) {
  PGame *this = (PGame*)context;

  if(this->logic_handler != NULL && this->render_handler != NULL) {
    // Do this frame
    layer_mark_dirty(this->canvas);
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Loop or Render handler not set!");
  }
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  // Woo hack!
  PGame *this = (PGame*)layer_get_data(layer);

  // Render and logic
  if(this->logic_handler != NULL && this->render_handler != NULL) {
    this->render_handler(ctx);
    this->logic_handler();

    // Next frame, only if stop has not been registered
    if(this->is_running == true) {
      this->render_timer = app_timer_register(PGAME_RENDER_DELTA, delta_handler, this);
    } else {
      destroy(this);
    }
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Loop or Render handler not set!");
  }
}

static void stop_rendering(PGame *this) {
  if(this->render_timer != NULL) {
    // Cancel any Timer
    app_timer_cancel(this->render_timer);
    this->render_timer = NULL;
  }

  // Will stop at the end of the next frame update_proc
  this->is_running = false;
}

static void start_rendering(PGame *this) {
  // Stop any current Timer
  stop_rendering(this);

  this->is_running = true;

  // Register new Timer to begin frame rendering loop
  this->render_timer = app_timer_register(PGAME_RENDER_DELTA, delta_handler, this);
}

static void destroy(PGame *this) {
  // Destroy canvas
  layer_destroy(this->canvas);

  free(this);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  PGame *this = (PGame*)context;
  this->click_handler(BUTTON_ID_SELECT);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  PGame *this = (PGame*)context;
  this->click_handler(BUTTON_ID_UP);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  PGame *this = (PGame*)context;
  this->click_handler(BUTTON_ID_DOWN);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}