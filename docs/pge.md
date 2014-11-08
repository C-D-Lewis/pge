# PGE Documentation

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

## Using Highscores

PGE supports basic highest-score recording that persists across app launches:

        int score = 9001;
        pge_title_set_highscore(score);

        int highscore = pge_title_get_highscore();

## Set a Game Background

You can easily set a background image for your game:

        pge_set_background(RESOURCE_ID_GAME_BACKGROUND);