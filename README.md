# pge

Simple looping game engine for Pebble.

## Compatibility with SDK 3.0

This repository will build for both the Aplite and Basalt platforms. If you
are still using SDK 2.9, you should rename `wscript-2.x` to `wscript`.

## Features

- Automatic looping of developer-supplied per-frame logic and rendering.
- 30 frames per second.
- Implement only your game code - `AppTimer`, `LayerUpdateProc`, `Clicks`,
  `Window` and `main` abstracted away.
- `PGESprite` base object to implement game entities.
- Basic collision checking between `PGESprite`s, GRects, lines and points.
- Isometric rendering of rects, boxes and textures.
- Basic game title screen template.
- Simple highscore mechanism.
- Centralized multiplayer through websockets


## Basic Template App

To begin a new game watchapp, begin with the template file in `/docs/`:

```
/**
 * This is the bare minimum to make a looping game with PGE!
 */

#include <pebble.h>
 
#include "pge/pge.h"

static Window *s_game_window;

static void game_logic() {
  // Per-frame game logic here

}

static void game_draw(GContext *ctx) {
  // Per-frame game rendering here

}

static void game_click(int button_id, bool long_click) {
  // Process click events

}

void pge_init() {
  // Start the game
  pge_begin(GColorBlack, game_logic, game_draw, game_click);

  // Keep a Window reference for adding other UI
  s_game_window = pge_get_window();
}

void pge_deinit() {
  // Finish the game
  pge_finish();
}
```

## Documentation

[PGE](docs/pge.md) - Main engine documentation.

[PGE Sprite](docs/pge_sprite.md) - Sprite class documentation.

[PGE Title](docs/pge_title.md) - Template title screen documentation.

[PGE Grid](docs/pge_grid.md) - Convenience for grid-based games.

[PGE Splash](docs/pge_splash.md) - Engine splash screen animation documentation.

[PGE Isometric](docs/pge_isometric.md) - Isometric rendering of rects, boxes and textures.

[PGE WS](docs/pge_ws/md) - WekSocket-based multiplayer with centralized server.
