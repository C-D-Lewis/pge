#include "main.h"

// UI
static Window *s_game_window;
static TextLayer *s_output_layer;

/******************************** WS Test *************************************/

static void ws_connection_handler(bool successful) {
  APP_LOG(APP_LOG_LEVEL_INFO, "ws_connection_handler");

  static char s_buff[32];
  snprintf(s_buff, sizeof(s_buff), "ID: %d", pge_ws_get_client_id());
  text_layer_set_text(s_output_layer, s_buff);
}

/******************************** Engine callbacks ****************************/

static void logic() {

}

static void draw(GContext *ctx) {

}

static void click(int button_id, bool long_click) {
  switch(button_id) {
    case BUTTON_ID_SELECT:
      if(pge_ws_is_connected()) {
        // Send test data
        if(pge_ws_packet_begin()) {
          pge_ws_add_int(PGE_WS_KEY_0, 42);
          pge_ws_packet_send();
        }
      }
      break;
  }
}

/********************************* App Foundation *****************************/

void pge_init() {
  // Begin game loop
  pge_begin(GColorBlack, logic, draw, click);
  s_game_window = pge_get_window();

  pge_ws_begin("ws://192.168.1.4:5000", ws_connection_handler);

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
}