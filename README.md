# cub3D

A first-person 3D maze renderer written in C with **MiniLibX**, built as part of the 42 curriculum (42 Kocaeli).
It reads a `.cub` scene file, validates the map and draws a textured 3D view in real time using **raycasting** (the DDA algorithm), in the style of early 90s first-person games.

## Features

- Real-time raycasting at 1280×720
- A different wall texture for each direction (north, south, east, west)
- Floor and ceiling colors set in the scene file
- Smooth movement and rotation (keys are tracked on press and release)
- Strict `.cub` file parsing and map validation: the map must be closed by walls, have exactly one player and use only valid characters
- A garbage collector to keep memory management safe and leak-free

## Building

The project targets **Linux** (MiniLibX for X11). You need `cc`, `make` and the X11 development libraries:

```bash
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev
```

Clone the repository and unpack MiniLibX:

```bash
git clone https://github.com/smighty42/Cub3d_.git
cd Cub3d_
unzip -o mlx.zip
make
```

Other Makefile rules: `make clean`, `make fclean`, `make re`.

## Usage

```bash
./cub3D maps/test.cub
```

### Controls

| Key | Action |
| --- | --- |
| `W` / `S` | Move forward / backward |
| `A` / `D` | Move left / right |
| `←` / `→` | Turn left / right |
| `ESC` or close the window | Quit |

## Scene file format (`.cub`)

```
NO ./textures/wall_red.xpm
SO ./textures/wall_blue.xpm
WE ./textures/wall_yellow.xpm
EA ./textures/wall_green.xpm

F 85,73,73
C 135,206,244

11111111111111111
10000000000000001
100S0000001111111
10000000001
10000000001111111
10000001100000001
10000000000000001
11111111111111111
```

| Identifier | Meaning |
| --- | --- |
| `NO` `SO` `WE` `EA` | Path to the `.xpm` texture for each wall direction |
| `F` / `C` | Floor / ceiling color as `R,G,B` (0–255) |
| `1` | Wall |
| `0` | Empty floor |
| `N` `S` `E` `W` | Player start position and the direction it faces |

The map must come last in the file and be fully surrounded by walls. Any error stops the program with a message.

## Project structure

```
.
├── cub3d.h                  # Main header: structs, constants, key codes
├── src/
│   ├── main.c               # Entry point, window and hook setup
│   ├── ray_casting.c        # DDA raycasting
│   ├── draw_wall.c          # Textured wall slices
│   ├── background.c         # Floor and ceiling
│   ├── player.c             # Player setup
│   ├── controller.c         # Key events and the main loop
│   ├── update_player_position.c
│   ├── gc.c / cleanup.c     # Garbage collector and cleanup
│   └── parser/
│       ├── elements/        # Textures, colors, map reading
│       ├── validation/      # Walls, enclosure, player checks
│       └── utils/
├── get_next_line/           # Line-by-line file reading
├── maps/                    # Example scene files
├── textures/                # Wall textures (.xpm)
└── mlx.zip                  # MiniLibX
```

## Authors

- **Serpil Mayti** ([@smighty42](https://github.com/smighty42)): raycasting, rendering, player movement and controls, texture and color loading, garbage collector and cleanup
- **İbrahim Taşkıran** ([@ibosta](https://github.com/ibosta)): `.cub` parser, map validation, wall drawing, get_next_line
