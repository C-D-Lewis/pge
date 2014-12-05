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

To begin a new game watchapp, begin with the template file in `/docs/`.

## Documentation

[PGE](docs/pge.md) - Main engine documentation.

[PGE Sprite](docs/pge_sprite.md) - Sprite class documentation.

[PGE Title](docs/pge_title.md) - Template title screen documentation.

[PGE Grid](docs/pge_grid.md) - Convenience for grid-based games.

[PGE Splash](docs/pge_splash.md) - Engine splash screen animation documentation.

## Features To Do

- Multiplayer?
