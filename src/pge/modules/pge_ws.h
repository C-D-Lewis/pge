/**
 * PGE Multiplayer module using WebSockets
 */

#pragma once

#include <pebble.h>

#define PGE_WS_LOGS true

// Developer-usable keys, MUST be declared in appinfo.json
#define PGE_WS_KEY_0  0
#define PGE_WS_KEY_1  1
#define PGE_WS_KEY_2  2
#define PGE_WS_KEY_3  3
#define PGE_WS_KEY_4  4
#define PGE_WS_KEY_5  5
#define PGE_WS_KEY_6  6
#define PGE_WS_KEY_7  7
#define PGE_WS_KEY_8  8
#define PGE_WS_KEY_9  9
#define PGE_WS_KEY_10 10
#define PGE_WS_KEY_11 11
#define PGE_WS_KEY_12 12
#define PGE_WS_KEY_13 13
#define PGE_WS_KEY_14 14
#define PGE_WS_KEY_15 15

// Send URL, receive confirmation
#define PGE_WS_URL        100
#define PGE_WS_CLIENT_ID  101

typedef enum {
  PGEWSConnectionStateDisconnected,
  PGEWSConnectionStateConnecting,
  PGEWSConnectionStateConnected
} PGEWSConnectionState;

// Handler for connection result
typedef void (PGEWSConnectedHandler)(bool successful);

/**
 * Connect to server. 
 * url - The URL of the remote server. E.g.: "ws://localhost:5000"
 * handler - The PGEWSConnectedHandler called when the connection attempt returns
 */
void pge_ws_connect(char *url, PGEWSConnectedHandler *handler);

/**
 * Returns true if connected, else false
 */
bool pge_ws_is_connected();

/**
 * Returns the client ID from the server
 */
int pge_ws_get_client_id();

/*
 * Begin creating a PGE WS packet
 * Returns true if creation was successful
 */
bool pge_ws_packet_begin();

/**
 * Send the PGE WS packet
 * Returns true if send was successful
 */
bool pge_ws_packet_send();

/**
 * Add an int to the dictionary
 * key - The integer key associated with the value
 * value - The value to be added
 * Returns true if the add succeeded, false if it failed or pge_ws_packet_begin() has not been called
 */
bool pge_ws_add_int(int key, int value);

/**
 * Add a C string to the dictionary
 * key - The integer key associated with the value
 * value - The value to be added
 * Returns true if the add succeeded, false if it failed or pge_ws_packet_begin() has not been called
 */
bool pge_ws_add_cstring(int key, char *cstring);
