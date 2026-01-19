*This project has been created as part of the 42 curriculum by smayti, itaskira.*

# cub3D

## Description
The program renders a first-person view of a maze based on a 2D map file.
The player can move and rotate within the environment while the scene is rendered in real time.


## Instructions

### Requirements
- Linux
- CC
- Make
- MiniLibX (provided by 42)

### Compilation
```bash
make
```

### Execution
```bash
./cub3D maps/example.cub
```

## Map Format
The map file must contain texture paths for each wall direction (NO, SO, WE, EA), floor and ceiling colors (F, C), and a valid map composed of `1` for walls, `0` for empty spaces, and exactly one player starting position (N, S, E, or W).

Example:
```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100001
10N001
100001
111111
```

## Resources
- YouTube tutorials related to raycasting and MiniLibX
- Lode Vandevenne – Raycasting tutorial
- MiniLibX documentation (42)
- Wolfenstein 3D engine technical overview
- Linux manual pages

### AI Usage
AI tools were used as a learning reference and to speed up the understanding process.

