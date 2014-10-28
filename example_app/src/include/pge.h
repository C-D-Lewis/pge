/**
 * Pebble Game Engine - A simple game engine for Pebble
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
 * - Customizable framerate
 * - Easy to use button events, as well as query functions
 *
 * Abstracted Pebble APIs (DO NOT REIMPLEMENT!):
 * - Clicks using a PGEClickHandler
 */

#include <pebble.h>

#ifndef PGE_H
#define PGE_H

 /********************************** Engine ***********************************/

// Function for user to place their per-frame game logic
typedef void (PGELogicHandler)();

// Function for user to use the GContext to draw their game items
typedef void (PGERenderHandler)(GContext *ctx);

// Function for user to implement button clicks
typedef void (PGEClickHandler)(int button_id);

/**
 * Create a full-screen Layer to use as a rendering canvas
 *
 * Note: The Click handler can be NULL to not implement
 */
void pge_begin(Window *parent, PGELogicHandler *logic_handler, PGERenderHandler *render_handler, PGEClickHandler *click_handler);

/**
 * Finish the game and clean up
 */
void pge_finish();

/**
 * Query the current state of a button
 */
bool pge_get_button_state(ButtonId button);

/**
 * Set the desired framerate (0 - 30)
 */
void pge_set_framerate(int new_rate);

/********************************** Sprite ************************************/

// Sprite base object
typedef struct {
  GBitmap *bitmap;
  GPoint position;
} PGESprite;

/**
 * Create a sprite object
 */
PGESprite* pge_sprite_create(GPoint position, int initial_resource_id);

/**
 * Destroy a sprite object
 */
void pge_sprite_destroy(PGESprite *this);

/**
 * Set the current animation frame
 */
void pge_sprite_set_frame(PGESprite *this, int resource_id);

/**
 * Draw the sprite's bitmap to the graphics context
 */
void pge_sprite_draw(PGESprite *this, GContext *ctx);

/**
 * Set the position of the sprite
 */
void pge_sprite_set_position(PGESprite *this, GPoint new_position);

/**
 * Get the position of the sprite
 */
GPoint pge_sprite_get_position(PGESprite *this);

/********************************** Collision *********************************/

bool pge_collide(PGESprite* sprite1, PGESprite *sprite2);

#endif