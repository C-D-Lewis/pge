/**
 * Pebble Game Engine - A simple game engine for Pebble
 * Version 1.0.0
 *
 * Author: 
 * Chris Lewis
 *
 * Source and example:
 * https://github.com/C-D-Lewis/pge
 *
 * Features:
 * - 30 frames per second
 * - Automatic game loop using PGELogicHandler and PGERenderHandler
 * - Easy to use button events, as well as query functions
 *
 * Abstracted Pebble APIs (DO NOT REIMPLEMENT!):
 * - Clicks using a PGEClickHandler
 */

#include <pebble.h>

#ifndef PGE_H
#define PGE_H

#define PGE_RENDER_DELTA 34 

// Function for user to place their per-frame game logic
typedef void (PGELogicHandler)();

// Function for user to use the GContext to draw their game items
typedef void (PGERenderHandler)(GContext *ctx);

// Function for user to implement button clicks
typedef void (PGEClickHandler)(int button_id);

// Structure containing internal game items
typedef struct {
  Window *parent;
  Layer *canvas;
  AppTimer *render_timer;

  PGELogicHandler *logic_handler;
  PGERenderHandler *render_handler;
  PGEClickHandler *click_handler;

  bool is_running;
  bool button_states[3];
} PGE;

/**
 * Create a full-screen Layer to use as a rendering canvas
 *
 * Note: The Click handler can be NULL to not implement
 */
PGE* pge_begin(Window *parent, PGELogicHandler *logic_handler, PGERenderHandler *render_handler, PGEClickHandler *click_handler);

/**
 * Finish the game and clean up
 */
void pge_finish(PGE *this);

/**
 * Query the current state of a button
 */
bool pge_get_button_state(PGE *this, ButtonId button);

#endif