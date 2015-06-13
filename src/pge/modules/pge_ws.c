#include "pge_ws.h"

static PGEWSConnectedHandler *s_connection_handler;

static PGEWSConnectionState s_connection_state = PGEWSConnectionStateDisconnected;
static DictionaryIterator *s_outbox_iter;
static int s_client_id;

static void in_recv_handler(DictionaryIterator *iter, void *context) {
  Tuple *tuple = dict_find(iter, PGE_WS_URL);
  if(tuple) {
    // Was the connection successful?
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

    // Call the developer callback
    s_connection_handler(s_connection_state == PGEWSConnectionStateConnected);
  }
}

static void parse_result(AppMessageResult result) {
  switch(result) {
    case APP_MSG_OK: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_OK"); break;
    case APP_MSG_SEND_TIMEOUT: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_SEND_TIMEOUT"); break;
    case APP_MSG_SEND_REJECTED: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_SEND_REJECTED"); break;
    case APP_MSG_NOT_CONNECTED: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_NOT_CONNECTED"); break;
    case APP_MSG_APP_NOT_RUNNING: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_APP_NOT_RUNNING"); break;
    case APP_MSG_INVALID_ARGS: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_INVALID_ARGS"); break;
    case APP_MSG_BUSY: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_BUSY"); break;
    case APP_MSG_BUFFER_OVERFLOW: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_BUFFER_OVERFLOW"); break;
    case APP_MSG_ALREADY_RELEASED: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_ALREADY_RELEASED"); break;
    case APP_MSG_CALLBACK_ALREADY_REGISTERED: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_CALLBACK_ALREADY_REGISTERED"); break;
    case APP_MSG_CALLBACK_NOT_REGISTERED: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_CALLBACK_NOT_REGISTERED"); break;
    case APP_MSG_OUT_OF_MEMORY: APP_LOG(APP_LOG_LEVEL_DEBUG, "APP_MSG_OUT_OF_MEMORY"); break;
    default: break;
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

bool pge_ws_packet_begin() {
  AppMessageResult result = app_message_outbox_begin(&s_outbox_iter);
  if(result != APP_MSG_OK) {
    parse_result(result);
    return false;
  } else {
    return true;
  }
}

bool pge_ws_packen_send() {
  AppMessageResult result = app_message_outbox_send();
  if(result != APP_MSG_OK) {
    parse_result(result);
    return false;
  } else {
    return true;
  }
}
