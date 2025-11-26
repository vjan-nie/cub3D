/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:31:48 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/26 12:29:08 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct 	s_map
{
	char	**grid;        // Mapa en forma de matriz de chars ('0','1','N','S','E','W')
	int		width;          // Ancho del mapa en tiles ("baldosas")
	int		height;         // Alto del mapa en tiles
	char	*tex_paths[4]; // Rutas a las texturas NO, SO, WE, EA
	int		floor_color;    // Color del suelo (F R,G,B)
	int		ceiling_color;  // Color del techo (C R,G,B)
}			t_map;

typedef struct	s_player
{
	double 	x;          // Posición X en el mundo (no en pixeles, en tiles + decimales)
	double 	y;          // Posición Y
	double 	dir_x;      // Dirección de la vista (vector normalizado)
	double 	dir_y;
	double 	plane_x;    // Vector plano de cámara (perpendicular a dir)
	double 	plane_y;
	double 	move_speed; // Velocidad de movimiento
	double 	rot_speed;  // Velocidad de rotación
}			t_player;

/* IMAGE: Se "dibuja" la imagen en buffer antes de cargarla de golpe y terminada a la ventana.
Si se renderizase la ventana a tiempo real, tendría que ir pixel por pixel en orden, lo que es demasiado lento,
así que daría lugar a distorsión de la imagen y nada de fluidez.

endian: indica el orden de los bytes en la representación de color dentro del buffer de la imagen.

En MLX (MiniLibX):

0 → little endian
(orden de bytes: BGRA)

1 → big endian
(orden de bytes: ARGB)

Normalmente en Linux casi siempre tendrás 0, es decir, little endian. */
typedef struct s_img
{
	void	*img_ptr;  // Puntero de MLX a la imagen
	char	*data;     // Dirección del buffer de píxeles
	int		bpp;       // Bytes por pixel
	int		line_len;  // Cuántos bytes ocupa cada línea
	int		endian;
	int		width;
	int		height;
}			t_img;

/* En lugar de reaccionar cuando una tecla se pulsa, se guarda su estado (true/false).
En cada iteración del loop se procesan los inputs acumulados → movimiento suave. */
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

typedef struct	s_cub3d
{
	void		*mlx;            // Handler de MLX
	void		*win;            // Ventana
	t_map		map;             // Información del mapa
	t_player	player;          // Info del jugador/cámara
	t_img		frame;           // Framebuffer
	t_img		textures[4];     // Texturas NO, SO, WE, EA
	int			screen_width;
	int			screen_height;
	t_input		key_code;        // Estado de teclas
}	t_cub3d;


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

/* Se usa uno por cada columna de la pantalla. 
DDA algorithm (Digital Differential Analyzer):
Recorrer tile por tile y comprobando qué casillas toca el rayo.
Es un algoritmo preciso y eficiente sin recurrir a trigonometría pesada.
*/
typedef struct	s_ray
{
	double	dir_x;      // Dirección del rayo
	double	dir_y;
	double	side_x;     // Distancia desde el origen hasta la próxima línea vertical *punto de partida del DDA
	double	side_y;
	double	delta_x;    // Distancia entre 2 cruces verticales del grid
	double	delta_y;
	double	perp;       // Distancia perpendicular a la pared (corregida): 
						//cálculo de longitud del rayo respecto al plano de cámara, y no la distancia real con el jugador (evitar fish-eye)
	int		map_x;      // Cuadrícula actual del mapa donde empieza el rayo (x)
	int		map_y;
	int		step_x;     // +1 o -1, dirección del DDA: dirección en la que se mueve el DDA.
	int		step_y;
	int		side;       // qué tipo de línea de la cuadrícula (grid) golpeó el rayo. 0 = golpe vertical, 1 = horizontal
	int		hit;        // 1 si el rayo golpea una pared
	int		line_h;     // Altura en pixeles de la pared proyectada: de start a end
	int		start;      // Pixel donde empieza la pared
	int		end;        // Pixel donde termina la pared
	int		color;      // Color final del píxel (si no se usan texturas)
}			t_ray;


#endif
