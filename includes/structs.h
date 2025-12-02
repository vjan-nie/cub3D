/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:31:48 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/02 14:16:15 by vjan-nie         ###   ########.fr       */
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
 * @var KEY_W: Key code for 'W' (Forward).
 * @var KEY_A: Key code for 'A' (Strafe Left).
 * @var KEY_S: Key code for 'S' (Backward).
 * @var KEY_D: Key code for 'D' (Strafe Right).
 * @var KEY_LEFT: Key code for the Left Arrow key (Rotate Left).
 * @var KEY_RIGHT: Key code for the Right Arrow key (Rotate Right).
 * @var KEY_ESC: Key code for the Escape key (Exit).
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
 * @var s_map::grid: Map represented as a dynamically allocated grid
 * (matrix) of characters ('0' for floor, '1' for wall, 'N', 'S', 'E', 'W'
 * for player start position).
 * @var s_map::width: Width of the map in tiles (grid columns).
 * @var s_map::height: Height of the map in tiles (grid rows).
 * @var s_map::tex_paths: Array of strings containing the file paths for the
 * four cardinal textures (NO, SO, WE, EA).
 * @var s_map::floor_color: The R,G,B color value for the floor (F),
 * represented as a single integer.
 * @var s_map::ceiling_color: The R,G,B color value for the ceiling (C).
 */
typedef struct	s_map
{
	char	**grid;			// Mapa en forma de matriz de chars ('0','1','N','S','E','W')
	int		width;			// Ancho del mapa en tiles ("baldosas")
	int		height;			// Alto del mapa en tiles
	char	*tex_paths[4];	// Rutas a las texturas NO, SO, WE, EA
	int		floor_color;	// Color del suelo (F R,G,B)
	int		ceiling_color;	// Color del techo (C R,G,B)
}			t_map;

/**
 * @struct s_player
 * @brief Represents the player's position and camera orientation.
 * This structure contains all dynamic state variables for the player and
 * the associated Raycasting camera.
 * @var s_player::x: Player's X-position in world coordinates.
 * @var s_player::y: Player's Y-position in world coordinates.
 * @var s_player::dir_x: X-component of the normalized view direction vector.
 * @var s_player::dir_y: Y-component of the normalized view direction vector.
 * @var s_player::plane_x: X-component of the camera plane vector.
 * @var s_player::plane_y: Y-component of the camera plane vector.
 * @var s_player::move_speed: Movement speed factor per frame.
 * @var s_player::rot_speed: Rotation speed factor per frame.
 */
typedef struct	s_player
{
	double	x;				// Posición X en el mundo (no en pixeles, en tiles + decimales)
	double	y;				// Posición Y
	double	dir_x;			// Dirección de la vista (vector normalizado)
	double	dir_y;
	double	plane_x;		// Vector plano de cámara (perpendicular a dir)
	double	plane_y;
	double	move_speed;		// Velocidad de movimiento 
	double	rot_speed;		// Velocidad de rotación (ángulo de rotación por frame, en radianes!)
}			t_player;

/* IMAGE: Se "dibuja" la imagen en buffer antes de cargarla de golpe y terminada
a la ventana.
Si se renderizase la ventana a tiempo real, tendría que ir pixel por pixel en 
orden, lo que es demasiado lento, así que daría lugar a distorsión de la imagen y
nada de fluidez.
endian: indica el orden de los bytes en la representación de color dentro del
buffer de la imagen.
En MLX (MiniLibX):
0 → little endian
(orden de bytes: BGRA)
1 → big endian
(orden de bytes: ARGB)
Normalmente en Linux casi siempre tendrás 0, es decir, little endian. */

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
 * @var s_img::img_ptr: MiniLibX's internal pointer (handler) to the image object.
 * @var s_img::data: Pointer to the image's pixel buffer, where drawing operations occur.
 * @var s_img::bpp: Bits per pixel (e.g., 32 for standard color depth).
 * @var s_img::line_len: Size of one image line in bytes (line length or stride).
 * @var s_img::endian: Byte order (0: little-endian/BGRA, 1: big-endian/ARGB).
 * @var s_img::width: Image width in pixels.
 * @var s_img::height: Image height in pixels.
 */
typedef struct	s_img
{
	void	*img_ptr;	// Puntero de MLX a la imagen
	char	*data;		// Dirección del buffer de píxeles
	int		bpp;		// Bytes por pixel
	int		line_len;	// Cuántos bytes ocupa cada línea
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
 * @var s_input::w: State of the 'W' key (Forward).
 * @var s_input::a: State of the 'A' key (Strafe Left).
 * @var s_input::s: State of the 'S' key (Backward).
 * @var s_input::d: State of the 'D' key (Strafe Right).
 * @var s_input::left: State of the Left Arrow key (Rotate Left).
 * @var s_input::right: State of the Right Arrow key (Rotate Right).
 * @var s_input::esc: State of the 'ESC' key (Exit/Close window).
 */
typedef struct	s_input
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
 * @var s_cub3d::mlx: MiniLibX connection handler.
 * @var s_cub3d::win: MiniLibX window pointer.
 * @var s_cub3d::map: Map and configuration data.
 * @var s_cub3d::player: Player/camera state.
 * @var s_cub3d::frame: Main framebuffer image.
 * @var s_cub3d::textures[4]: Array of texture images (NO, SO, WE, EA).
 * @var s_cub3d::screen_width: Window width in pixels.
 * @var s_cub3d::screen_height: Window height in pixels.
 * @var s_cub3d::key_code: Current state of keyboard inputs.
 */
typedef struct	s_cub3d
{
	void		*mlx;			// Handler de MLX
	void		*win;			// Ventana
	t_map		map;			// Información del mapa
	t_player	player;			// Info del jugador/cámara
	t_img		frame;			// Framebuffer
	t_img		textures[4];	// Texturas NO, SO, WE, EA
	int			screen_width;
	int			screen_height;
	t_input		key_code;		// Estado de teclas
}	t_cub3d;


/* Se usa uno por cada columna de la pantalla. 
DDA algorithm (Digital Differential Analyzer):
Recorrer tile por tile y comprobando qué casillas toca el rayo.
Es un algoritmo preciso y eficiente sin recurrir a trigonometría pesada.
*/
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
 * @var s_ray::dir_x: X-component of the ray's direction vector.
 * @var s_ray::dir_y: Y-component of the ray's direction vector.
 * @var s_ray::side_x: Distance from the ray's origin to the next vertical
 * grid line.
 * @var s_ray::side_y: Distance from the ray's origin to the next horizontal
 * grid line.
 * @var s_ray::delta_x: Distance the ray travels to cross one unit in
 * X direction.
 * @var s_ray::delta_y: Distance the ray travels to cross one unit in
 * Y direction.
 * @var s_ray::perp: Perpendicular distance from the camera plane to the
 * hit wall. Used to calculate wall height and prevents the "fish-eye" effect.
 * @var s_ray::map_x: X-coordinate of the current map tile the ray is in.
 * @var s_ray::map_y: Y-coordinate of the current map tile the ray is in.
 * @var s_ray::step_x: Direction to step in the X-axis for the DDA algorithm.
 * @var s_ray::step_y: Direction to step in the Y-axis for the DDA algorithm.
 * @var s_ray::side: Indicates which side of the wall was hit
 * (0 for vertical line hit, 1 for horizontal line hit).
 * @var s_ray::hit: Flag (1) if the ray has hit a wall, (0) otherwise.
 * @var s_ray::line_h: Height of the projected wall slice in pixels.
 * @var s_ray::start: Starting pixel (Y-coordinate) on the screen where the
 * projected wall line begins.
 * @var s_ray::end: Ending pixel (Y-coordinate) on the screen where the projected
 * wall line ends.
 * @var s_ray::color: Final color of the pixel.
 */
typedef struct	s_ray
{
	double	dir_x;		// Dirección del rayo
	double	dir_y;
	double	side_x;		// Distancia desde el origen hasta la próxima línea vertical *punto de partida del DDA
	double	side_y;
	double	delta_x;	// Distancia entre 2 cruces verticales del grid
	double	delta_y;
	double	perp;		// Distancia perpendicular a la pared (corregida): 
						//cálculo de longitud del rayo respecto al plano de cámara, y no la distancia real con el jugador (evitar fish-eye)
	int		map_x;		// Cuadrícula actual del mapa donde empieza el rayo (x)
	int		map_y;
	int		step_x;		// +1 o -1, dirección del DDA: dirección en la que se mueve el DDA.
	int		step_y;
	int		side;		// qué tipo de línea de la cuadrícula (grid) golpeó el rayo. 0 = golpe vertical, 1 = horizontal
	int		hit;		// 1 si el rayo golpea una pared
	int		line_h;		// Altura en pixeles de la pared proyectada: de start a end
	int		start;		// Pixel donde empieza la pared
	int		end;		// Pixel donde termina la pared
	int		color;		// Color final del píxel (si no se usan texturas)
}			t_ray;

#endif