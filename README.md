# pge

Simple looping game engine for Pebble. This repo is designed to be cloned into
an existing Pebble project's `src` directory.

## Installation

1. `pebble new-project your_game_project`
2. `cd your_game_project/src`
3. `git clone https://github.com/C-D-Lewis/pge`
4. `#include "pge/pge.h"`


## Features

- Automatic looping of developer-supplied per-frame logic and rendering.
- Up to 30 frames per second.
- Implement only your game code - `AppTimer`, `LayerUpdateProc`, `Clicks`,
  `Window` and `main` abstracted away.
- `PGESprite` base object to implement game entities.
- Basic collision checking between `PGESprite`s, GRects, lines and points.
- Isometric rendering of rects, boxes and textures.
- Basic game title screen template.
- Simple highscore mechanism.
- WebSocket-based client-server abstraction.


## Examples

Get example implementations of PGE games in the 
[pge-examples](https://github.com/C-D-Lewis/pge-examples) repo.


## Basic Template App

To begin a new game watchapp, begin with the template file in `/docs/template.c.sample`:

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

[PGE WS](docs/pge_ws.md) - WebSocket-based client-server abstraction.
