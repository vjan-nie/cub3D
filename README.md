# cub3D

A first-person raycasting engine in C, in the spirit of Wolfenstein 3D. Built with a partner at 42 Madrid.

**Tech:** C · MLX graphics · raycasting · linear algebra

## What it does
Renders a textured maze in first person from a 2D map, in real time: the player walks and turns through the world while the engine casts rays to draw the walls.

## What I worked on
The work was split between the two of us: my partner owned the `.cub` file parser (map and scene configuration), and I owned the **rendering** — the raycasting engine:

- **DDA ray casting** to find the first wall each ray hits as it steps through the map grid.
- **Fisheye correction**, projecting along the camera direction so straight walls don't bow at the edges of the view.
- **Wall textures by orientation**, choosing the right texture for north/south/east/west faces.
- **Player movement and rotation**, with wall collisions handled directly inside the movement logic.

## Design decisions
- **DDA for ray traversal.** Instead of stepping each ray by tiny fixed increments, DDA jumps from grid line to grid line — fewer steps, exact wall hits, and the cleanest form of the math. It was the part I enjoyed most: once the geometry clicked, the rest of the renderer fell into place.

## Limitations / what I'd improve
Scope was the mandatory specification (no minimap, doors, sprites or mouse rotation). Collisions weren't a separate feature — they fell out of the movement logic naturally.

## Build & run
```sh
make
./cub3D maps/<map>.cub
```

## Authors

- **serjimen** - Sergio Jiménez
- **vjan-nie** - Vadim Jan
