#include "pge_ws.h"

static PGEWSConnectedHandler *s_connection_handler;

static PGEWSConnectionState s_connection_state = PGEWSConnectionStateDisconnected;
static int s_client_id;

static void in_recv_handler(DictionaryIterator *iter, void *context) {
  Tuple *tuple = dict_find(iter, PGE_WS_URL);
  if(tuple) {
    s_connection_state = (tuple->value->int32 == 1) ? PGEWSConnectionStateConnected : PGEWSConnectionStateDisconnected;
    if(PGE_WS_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "PGE_WS: Connection result: %s", s_connection_state ? "OK" : "FAILED");

    // Store client ID in this bundle
    Tuple *id_tuple = dict_find(iter, PGE_WS_CLIENT_ID);
    if(id_tuple) {
      s_client_id = id_tuple->value->int32;
      if(PGE_WS_LOGS) APP_LOG(APP_LOG_LEVEL_INFO, "Got ID %d", s_client_id);
    } else {
      s_connection_state = PGEWSConnectionStateDisconnected;
      if(PGE_WS_LOGS) APP_LOG(APP_LOG_LEVEL_ERROR, "CLient ID was not provided by the server.");
    }
    s_connection_handler(s_connection_state == PGEWSConnectionStateConnected);
  }
}

void pge_ws_connect(char *url, PGEWSConnectedHandler *handler) {
  if(s_connection_state == PGEWSConnectionStateDisconnected) {
    // Set up callbacks
    s_connection_handler = handler;
    app_message_register_inbox_received(in_recv_handler);
    app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
    if(PGE_WS_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "PGE_WS: AppMessage opened");

    // Send URL to JS
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    dict_write_cstring(iter, PGE_WS_URL, url);
    app_message_outbox_send();
    if(PGE_WS_LOGS) APP_LOG(APP_LOG_LEVEL_DEBUG, "PGE_WS: URL sent");
  } else {
    if(PGE_WS_LOGS) APP_LOG(APP_LOG_LEVEL_INFO, "PGE_WS: Already connected, or connection in progress!");
  }
}

bool pge_ws_is_connected() {
  return s_connection_state == PGEWSConnectionStateConnected;
}

int pge_ws_get_client_id() {
  return s_client_id;
}