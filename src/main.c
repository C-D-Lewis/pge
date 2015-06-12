#include "main.h"

// UI
static Window *s_game_window;
static TextLayer *s_output_layer;

/******************************** WS Test *************************************/

static void ws_connection_callback(bool successful) {
  APP_LOG(APP_LOG_LEVEL_INFO, "ws_connection_callback: %d" + pge_ws_get_client_id());
  pge_ws_disconnect();
}

static void connect() {
  pge_ws_connect("ws://localhost:5000", ws_connection_callback);
}

/******************************** Engine callbacks ****************************/

static void logic() {

}

static void draw(GContext *ctx) {

}

static void click(int button_id, bool long_click) {
  switch(button_id) {
    case BUTTON_ID_SELECT:
      connect();
      break;
  }
}

/********************************* App Foundation *****************************/

void pge_init() {
  // Begin game loop
  pge_begin(GColorBlack, logic, draw, click);
  s_game_window = pge_get_window();
  pge_set_framerate(25);

  // Create score layer
  s_output_layer = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_text_color(s_output_layer, GColorWhite);
  text_layer_set_background_color(s_output_layer, GColorBlack);
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  layer_add_child(window_get_root_layer(s_game_window), text_layer_get_layer(s_output_layer)); 
}

void pge_deinit() {
  // Destroy score layer
  text_layer_destroy(s_output_layer);

  // End game loop
  pge_finish();
  pge_ws_disconnect();
}