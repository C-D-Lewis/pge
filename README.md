# pge

Simple looping game engine for Pebble.

![screenshot](screenshots/screenshot1.png)

> Example app sees the user control a simple robot.

## Features

- Automatic looping of developer-supplied per-frame logic and rendering.
- 30 frames per second.
- `AppTimer`, `LayerUpdateProc` and `Clicks` abstracted away. Implement only
  your game code.
- `PGESprite` base object to implement game entities.
- Basic collision checking between `PGESprite`s.
- Basic game title screen helper.

## Starting and Stopping Your Game

1. Copy `src/pge/` to your project's `src` directory.

2. Add `#include "pge/pge.h"` to your project's main C file.

3. Implement one of `PGELogicHandler`, `PGERenderHandler` and
   `PGEClickHandler`:

        void logic() {
          
        }

        void draw(GContext *ctx) {
          
        }

        // Optional, can be NULL if only using pge_get_button_state()
        void click(int button_id) {
          
        }

4. Call `pge_begin()`, supplying the `Window` it will reside in as well as your
   callbacks:

        pge_begin(s_window, logic, draw, click);

5. Furnish `logic()`, `render()` and `click()` to implement your own game items
   and logic. See `examples` for an example implementation.

6. When done (i.e: when the host Window is being destroyed), destroy the engine:

        static void main_window_unload(Window *window) {
          // Destroy all game resources
          pge_finish();
        }

## Creating Game Sprites

The `PGESprite` structure allows creation of a bitmap sprite-based game entity
and a set of convenience functions to manage it.

 * Include `pge/additional/pge_sprite.h` in your main C file:

        #include "pge/additional/pge_sprite.h"

 * Create a structure containing a `PGESprite` pointer member:

        typedef struct {
          PGESprite *sprite;
          int direction;
          bool moving;
        } Robot;

 * Create the `PGESprite` when the entity is created:

        this->sprite = pge_sprite_create(start_position, RESOURCE_ID_ROBOT_UP);

 * Update the sprite's bitmap as the player plays the game:

        // Set the sprite bitmap
        switch(this->direction) {
          case DIRECTION_UP:
            pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_UP);
            break;
          case DIRECTION_RIGHT:
            pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_RIGHT);
            break;
          case DIRECTION_DOWN:
            pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_DOWN);
            break;
          case DIRECTION_LEFT:
            pge_sprite_set_frame(this->sprite, RESOURCE_ID_ROBOT_LEFT);
            break;
        }

 * Update the entity's position:

        GPoint pos = GPoint(25 + dx, 25 + dy);
        pge_sprite_set_position(this->sprite, pos);

or to move by a certain number of pixels:

        // Move by (10, 0)
        pge_sprite_move(this->sprite, 10, 0);

 * Draw the entity's bitmap:

        pge_sprite_draw(this->sprite, ctx);

 * Destroy the entity's `PGESprite` when destroying the app:

        void robot_destroy(Robot *this) {
          pge_sprite_destroy(this->sprite);
          free(this);
        }

## Showing a Title Screen

Using `pge_title.h` allows easy creation of a simple game title screen. It is
assumed that the title screen will be the first thing the user sees, and so at
the bottom of the Window stack.

1. Include the header file:

        #include "pge/additional/pge_title.h"

2. Push the title screen window in your app initialization to show it first.
   Provide a title, the colour of the title text, the resource ID of the
   background image (144 x 168) and a PGEClickHandler implementation to handle
   clicks on the title screen:

        static void init(void) {
          pge_title_push("Robot Example Game", GColorWhite, RESOURCE_ID_TITLE_BG, title_click);
        }

3. When your app exits, pop the last window:

        static void deinit(void) {
          pge_title_pop();
        }

## Features To Do

- Proper docs

- Grid-restricted mode for implementing RPG-style games.

- Title screen

- Highscores
