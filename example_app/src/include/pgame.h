/**
 * PGame - A simple game engine for Pebble
 * Version 1.0.0
 *
 * Author: 
 * Chris Lewis
 *
 * Source and example:
 * https://github.com/C-D-Lewis/pgame
 *
 * Features:
 * - 30 frames per second
 * - Automatic game loop using PGameLogicHandler and PGameRenderHandler
 * - Easy to use button events
 *
 * Abstracted Pebble APIs (DO NOT REIMPLEMENT!):
 * - Clicks using a PGameClickHandler
 */

#include <pebble.h>

#ifndef PGAME_H
#define PGAME_H

#define PGAME_RENDER_DELTA 34 

// Function for user to place their per-frame game logic
typedef void (PGameLogicHandler)();

// Function for user to use the GContext to draw their game items
typedef void (PGameRenderHandler)(GContext *ctx);

// Function for user to implement button clicks
typedef void (PGameClickHandler)(int button_id);

// Structure containing internal game items
typedef struct {
  Window *parent;
  Layer *canvas;
  AppTimer *render_timer;

  PGameLogicHandler *logic_handler;
  PGameRenderHandler *render_handler;
  PGameClickHandler *click_handler;

  bool is_running;
} PGame;

/**
 * Create a full-screen Layer to use as a rendering canvas
 *
 * Note: The Click handler can be NULL to not implement
 */
PGame* pgame_begin(Window *parent, PGameLogicHandler *logic_handler, PGameRenderHandler *render_handler, PGameClickHandler *click_handler);

/**
 * Finish the game and clean up
 */
void pgame_finish(PGame *this);

#endif