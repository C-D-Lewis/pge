# pge

Simple looping game engine for Pebble.

![screenshot](screenshots/screenshot1.png)

> Example app sees the user control a simple robot.

## Features

- Automatic looping of developer-supplied per-frame logic and rendering.
- 30 frames per second.
- `AppTimer`, `LayerUpdateProc` and `Clicks` abstracted away. Implement only
  your game code.

## How to Use

1. Copy `src/pge.h` and `src/pge.c` to your project's `src` directory.

2. Add `#include "pge.h"` to your project's main C file.

3. Implement one of `PGELogicHandler`, `PGERenderHandler` and
   `PGEClickHandler`.

        void loop() {
          
        }

        void draw(GContext *ctx) {
          
        }

        void click(int button_id) {
          
        }

4. Create an instance of `PGE`, supplying the `Window` it will reside in.

        static PGE *s_game;

        ...

        s_game = pge_begin(s_window, loop, draw, click);

5. Furnish `loop()`, `render()` and `click()` to implement your own game items
   and logic. See `example_app` for an example implementation.

6. When done (i.e: when the host Window is being destroyed), destroy your
   `PGE`.

        static void main_window_unload(Window *window) {
          // Destroy all game resources
          pge_finish(s_game);
        }

## Features To Do

- List of entities to allow automated execution of their logic and rendering.
  This will also allow collision checking.

- Grid-restricted mode for implementing RPG-style games.