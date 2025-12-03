/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:31:48 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/03 18:43:50 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file structs.h
 * @brief Contains all the primary data structures for the cub3D project.
 * This header defines the essential data structures used throughout the
 * application, including map configuration, player state, MiniLibX image
 * handlers, input state, and the main context structure (t_cub3d).
 * It also includes the structure for the Raycasting process (t_ray)
 * and key code definitions.
 */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

/**
 * @enum e_keycode
 * @brief Defines the key codes used for standard movement and control
 * inputs in MinilibX.
 * @param KEY_W: Key code for 'W' (Forward).
 * @param KEY_A: Key code for 'A' (Strafe Left).
 * @param KEY_S: Key code for 'S' (Backward).
 * @param KEY_D: Key code for 'D' (Strafe Right).
 * @param KEY_LEFT: Key code for the Left Arrow key (Rotate Left).
 * @param KEY_RIGHT: Key code for the Right Arrow key (Rotate Right).
 * @param KEY_ESC: Key code for the Escape key (Exit).
 */
typedef enum e_keycode
{
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_ESC = 65307
}	t_keycode;

/**
 * @struct s_map
 * @brief Stores the configuration and data of the map loaded from
 * the .cub file.
 * This structure holds all static information related to the game world
 * read during the parsing phase.
 * @param grid: Map represented as a dynamically allocated grid
 * (matrix) of characters ('0' for floor, '1' for wall, 'N', 'S', 'E', 'W'
 * for player start position).
 * @param width: Width of the map in tiles (grid columns).
 * @param height: Height of the map in tiles (grid rows).
 * @param tex_paths: Array of strings containing the file paths for the
 * four cardinal textures (NO, SO, WE, EA).
 * @param floor_color: The R,G,B color value for the floor (F),
 * represented as a single integer.
 * @param ceiling_color: The R,G,B color value for the ceiling (C).
 */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*tex_paths[4];
	int		floor_color;
	int		ceiling_color;
}			t_map;

/**
 * @struct s_player
 * @brief Represents the player's position and camera orientation.
 * This structure contains all dynamic state variables for the player and
 * the associated Raycasting camera.
 * @param x: Player's X-position in world coordinates.
 * @param y: Player's Y-position in world coordinates.
 * @param dir_x: X-component of the normalized view direction vector.
 * @param dir_y: Y-component of the normalized view direction vector.
 * @param plane_x: X-component of the camera plane vector.
 * @param plane_y: Y-component of the camera plane vector.
 * @param move_speed: Movement speed factor per frame.
 * @param rot_speed: Rotation speed factor per frame, in radians.
 */
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}			t_player;

/**
 * @struct s_img
 * @brief Represents an image used by MiniLibX, either as a framebuffer
 * or a texture.
 * This structure encapsulates the necessary pointers and metadata to manage
 * a graphic image in the MiniLibX environment.
 * @details
 * An image is drawn into a buffer (data) before being loaded (put) onto
 * the window to prevent screen tearing and achieve fluid rendering.
 * The `endian` field indicates the byte order for color representation within
 * the buffer (0: little-endian, 1: big-endian).
 * @param img_ptr: MiniLibX's internal pointer to the image struct.
 * @param data: Pointer to the image's pixel buffer, 
 * where drawing operations occur.
 * @param bpp: Bits per pixel (e.g., 32 for standard color depth).
 * @param line_len: Size of one image line in bytes (line length or stride).
 * @param endian: Byte order (0: little-endian/BGRA, 1: big-endian/ARGB).
 * @param width: Image width in pixels.
 * @param height: Image height in pixels.
 */
typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

/**
 * @struct s_input
 * @brief Tracks the continuous state (pressed/released) of movement and
 * control keys.
 * Instead of reacting to single key presses, the state is accumulated in
 * this structure and processed once per main loop iteration, ensuring
 * smooth movement.
 * @param w: State of the 'W' key (Forward).
 * @param a: State of the 'A' key (Strafe Left).
 * @param s: State of the 'S' key (Backward).
 * @param d: State of the 'D' key (Strafe Right).
 * @param left: State of the Left Arrow key (Rotate Left).
 * @param right: State of the Right Arrow key (Rotate Right).
 * @param esc: State of the 'ESC' key (Exit/Close window).
 */
typedef struct s_input
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	esc;
}			t_input;

/**
 * @struct s_cub3d
 * @brief The main context structure for the entire application.
 * This structure aggregates all essential data structures and MiniLibX
 * handlers, serving as the central hub of the game state. This structure
 * is typically passed around to functions that need access to the global state.
 * @param mlx: MiniLibX connection handler.
 * @param win: MiniLibX window pointer.
 * @param map: Map and configuration data.
 * @param player: Player/camera state.
 * @param frame: Main framebuffer image.
 * @param textures[4]: Array of texture images (NO, SO, WE, EA).
 * @param screen_width: Window width in pixels.
 * @param screen_height: Window height in pixels.
 * @param key_code: Current state of keyboard inputs.
 */
typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		frame;
	t_img		textures[4];
	int			screen_width;
	int			screen_height;
	t_input		key_code;
}	t_cub3d;

/**
 * @struct s_ray
 * @brief Holds all intermediate and final parameters for a single ray 
 * during Raycasting.
 * Raycasting is performed one column at a time. This structure holds
 * the necessary data for the Digital Differential Analyzer (DDA)
 * algorithm and projection results.
 * @details
 * The Digital Differential Analyzer (DDA) algorithm is used to efficiently
 * traverse the map grid, checking which tiles the ray intersects without
 * heavy trigonometric calculations at every step. This structure is typically
 * initialized and reused within the main rendering loop for each screen column.
 * @param dir_x: X-component of the ray's direction vector.
 * @param dir_y: Y-component of the ray's direction vector.
 * @param side_x: Distance from the ray's origin to the next vertical
 * grid line.
 * @param side_y: Distance from the ray's origin to the next horizontal
 * grid line.
 * @param delta_x: Distance the ray travels to cross one unit in
 * X direction.
 * @param delta_y: Distance the ray travels to cross one unit in
 * Y direction.
 * @param perp: Perpendicular distance from the camera plane to the
 * hit wall. Used to calculate wall height and prevents the "fish-eye" effect.
 * @param map_x: X-coordinate of the current map tile the ray is in.
 * @param map_y: Y-coordinate of the current map tile the ray is in.
 * @param step_x: Direction to step in the X-axis for the DDA algorithm.
 * @param step_y: Direction to step in the Y-axis for the DDA algorithm.
 * @param side: Indicates which side of the wall was hit
 * (0 for vertical line hit, 1 for horizontal line hit).
 * @param hit: Flag (1) if the ray has hit a wall, (0) otherwise.
 * @param line_h: Height of the projected wall slice in pixels.
 * @param start: Starting pixel (Y-coordinate) on the screen where the
 * projected wall line begins.
 * @param end: Ending pixel (Y-coordinate) on the screen where the projected
 * wall line ends.
 * @param color: Final color of the pixel.
 */
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	perp;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_h;
	int		start;
	int		end;
	int		color;
}			t_ray;

#endif