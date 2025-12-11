# cub3D - My First RayCaster with miniLibX

![Language](https://img.shields.io/badge/Language-C-blue)
![Library](https://img.shields.io/badge/Library-MiniLibX-orange)
![Subject](https://img.shields.io/badge/42-cub3D-green)

<div align="center">
  <video src="img/gameplay.webm" width="100%" controls muted autoplay></video>
  <br>
  <em>Gameplay Demo</em>
</div>

## Introduction
**cub3D** is a project inspired by the world-famous 90's game *Wolfenstein 3D*, considered the first FPS ever created. This project explores the **Raycasting** technique to create a dynamic 3D view inside a maze.

The goal is to create a realistic 3D graphical representation of the inside of a maze from a first-person perspective using the C language and the miniLibX library.

## Features
This project implements the complete **Mandatory** part of the subject:

* **Raycasting Engine:** Real-time 3D rendering using the DDA (Digital Differential Analyzer) algorithm.
* **Texture Mapping:** Displays 4 different wall textures depending on the wall's orientation (North, South, East, West).
* **Color Rendering:** Distinct floor and ceiling colors parsed from configuration.
* **Smooth Movement:**
    * `W`, `A`, `S`, `D` movement[cite: 120].
    * Left/Right camera rotation[cite: 119].
    * **Collision System:** Includes wall sliding and hitboxes to prevent clipping.
* **Robust Parsing:**
    * Handles map files (`.cub`) with strict validation.
    * Checks for closed maps (surrounded by walls).
    * Validates RGB ranges and file format.

## Installation & Usage

### Prerequisites
* GCC compiler.
* Make.
* X11 include files (usually available on Linux/Unix systems).

### Compilation
Clone the repository and compile the project using the Makefile rules:

```bash
make        # Compiles the executable 'cub3D'
make re     # Recompiles everything
make clean  # Removes object files
make fclean # Removes object files and executable
```

### Running the Game

To start the game, provide a valid `.cub` map file as an argument:

```bash
./cub3D maps/subject_map.cub
```

### Controls

| Key | Action |
| :--- | :--- |
| `W` | Move Forward |
| `S` | Move Backward |
| `A` | Strafe Left |
| `D` | Strafe Right |
| `←` | Rotate Camera Left |
| `→` | Rotate Camera Right |
| `ESC` | Close Game |
| `[X]` | Close Window (Red Cross) |

## Map Configuration (`.cub`)

The program parses a file with the following structure:

1.  **Textures:** Paths to XPM files for each cardinal direction.
    ```
    NO ./path_to_north_texture.xpm
    SO ./path_to_south_texture.xpm
    WE ./path_to_west_texture.xpm
    EA ./path_to_east_texture.xpm
    ```
2.  **Colors:** RGB values (0-255) for Floor (F) and Ceiling (C).
    ```
    F 220,100,0
    C 225,30,0
    ```
3.  **The Map:** A grid of characters where `1` is a wall, `0` is empty space, and `N/S/E/W` is the player start position.
    ```
    111111
    100101
    101001
    1100N1
    111111
    ```

-----

## Technical Implementation

### 1\. The Parser

The parsing phase is designed to be fail-safe. It follows a strict pipeline:

1.  **Read:** Reads the whole file and identifies the map block.
2.  **Config Parse:** Extracts textures and colors, checking for duplicates and valid ranges (0-255).
3.  **Map Extraction:** Extracts the grid and **normalizes** it to a rectangle (padding with spaces converted to walls).
4.  **Validation:**
      * Ensures only valid characters exist (`0, 1, N, S, E, W`).
      * **Flood/Boundary Check:** Ensures the player is not on the edge and the map is strictly closed by walls.

### 2\. Raycasting Algorithm (DDA)

The core rendering loop works column by column (x = 0 to Screen Width):

1.  **Ray Calculation:**

      * A ray is cast from the player's position.
      * `ray_dir` is calculated using the player's `direction` vector and the `camera_plane` vector (which determines FOV).

2.  **DDA (Digital Differential Analyzer):**

      * The ray advances through the grid one square at a time using `delta_dist` and `side_dist`.
      * This ensures we don't skip walls and is computationally efficient.

3.  **Fisheye Correction:**

      * Instead of Euclidean distance, we calculate the **perpendicular distance** from the camera plane to the wall. This prevents straight walls from looking curved.
      * Formula: `perp_dist = (side_dist - delta_dist)`.

4.  **Texture Mapping:**

      * We calculate `wall_x` (the exact hit point on the wall 0.0 to 1.0).
      * We map this to the texture width (`tex_x`) and draw the vertical strip pixel by pixel.

## Project Structure

  * **`src/core`**: Main loop and window management.
  * **`src/parser`**: Map reading, validation, and configuration parsing.
  * **`src/render`**: Raycasting algorithm and drawing routines.
  * **`includes`**: Header files (`cub3d.h`, `structs.h`).
  * **`libft`**: Custom C library.

## Error Handling

The program includes robust error management. It will explicitly print `Error\n` followed by a specific message and exit cleanly (freeing memory) in cases of:

  * Invalid arguments.
  * Map misconfiguration (missing textures, invalid colors).
  * Open map borders.
  * Memory allocation failures.

## Authors

- **vjan-nie** - Vadim Jan
- **serjimen** - Sergio Jiménez