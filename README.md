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
- Basic game title screen template.
- Simple highscore mechanism.

## Documentation

[PGE](docs/pge.md)

[PGE Sprite](docs/pge_sprite.md)

[PGE Title](docs/pge_title.md)

## Features To Do

- Multiplayer?
