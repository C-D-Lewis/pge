# pge

Simple looping game engine for Pebble.

## Features

- Automatic looping of developer-supplied per-frame logic and rendering.
- 30 frames per second.
- `AppTimer`, `LayerUpdateProc`, `Clicks`, `Window` and `main` abstracted away.
  Implement only your game code.
- `PGESprite` base object to implement game entities.
- Basic collision checking between `PGESprite`s, GRects, lines and points.
- Basic game title screen template.
- Simple highscore mechanism.

## Basic Template App

To begin a new game watchapp, begin with the following code:

        #include <pebble.h>
        #include "pge/pge.h"

        static Window *s_game_window;

        // Implement per-frame game logic
        static void game_logic() {

        }

        // Implement per-frame game drawing
        static void game_draw(GContext *ctx) {

        }

        // React to button click events
        static void game_click(int button_id) {

        }

        // App setup 
        void pge_init() {
          // Begin game loop Window
          s_game_window = pge_begin(game_logic, game_draw, game_click);
        }

        // App teardown
        void pge_deinit() {
          pge_finish();
        }

## Documentation

[PGE](docs/pge.md)

[PGE Sprite](docs/pge_sprite.md)

[PGE Title](docs/pge_title.md)

## Features To Do

- Multiplayer?
