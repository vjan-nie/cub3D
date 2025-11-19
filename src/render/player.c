/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:46:20 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:39:00 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Busca la posición del jugador en el mapa y devuelve la dirección inicial.
// También inicializa la posición exacta del jugador en coordenadas de mundo (centro de la celda)
static char	get_player_dir(t_map *map, t_player *p)
{
	int	px;
	int	py;
	char	dir;

	px = 0;
	py = 0;
	// Encuentra la celda del jugador ('N', 'S', 'E', 'W') y devuelve el carácter
	dir = find_player_tile(map, &px, &py);

	// Posición del jugador en coordenadas de mundo (centrada en la celda)
	p->x = px + 0.5;
	p->y = py + 0.5;

	return (dir);
}

// Inicializa los vectores de dirección y del plano de visión del jugador
static void	set_values(t_player *p, double dx, double dy, double px, double py)
{
	p->dir_x = dx;    // Vector de dirección en X
	p->dir_y = dy;    // Vector de dirección en Y
	p->plane_x = px;  // Vector perpendicular a la dirección (para el FOV)
	p->plane_y = py;
}

// Configura la dirección y el plano de visión según la letra del mapa ('N', 'S', 'E', 'W')
static void	set_dir_and_plane(t_player *p, char dir)
{
	if (dir == 'N')
		set_values(p, 0, -1, 0.66, 0);   // Mirando hacia arriba (Y negativo)
	else if (dir == 'S')
		set_values(p, 0, 1, -0.66, 0);   // Mirando hacia abajo (Y positivo)
	else if (dir == 'E')
		set_values(p, 1, 0, 0, 0.66);    // Mirando hacia derecha (X positivo)
	else if (dir == 'W')
		set_values(p, -1, 0, 0, -0.66);  // Mirando hacia izquierda (X negativo)
}

// Inicializa los valores del jugador al inicio del juego
// - Posición basada en el mapa
// - Dirección y plano de visión inicial
// - Velocidades de movimiento y rotación
void	init_player(t_player *p, t_map *map)
{
	char	dir;

	dir = get_player_dir(map, p); // Determina la posición y dirección inicial
	p->move_speed = 0.05;          // Velocidad de movimiento por frame
	p->rot_speed = 0.05;           // Velocidad de rotación por frame
	set_dir_and_plane(p, dir);      // Configura los vectores de dirección y plano
}

/* Posición centrada

p->x = px + 0.5; asegura que el jugador comience en el centro de la celda, no en la esquina. Esto evita problemas de colisión inmediata con paredes.

Vectores de dirección y plano

dir_x, dir_y determinan hacia dónde “mira” el jugador.

plane_x, plane_y determinan la proyección del FOV para el renderizado tipo raycaster.

Los valores 0.66 definen un FOV de aproximadamente 66°, típico en cub3D.

Flexibilidad

Cambiando move_speed y rot_speed puedes ajustar la sensibilidad del movimiento y la rotación.

Conexión con otras funciones

Los vectores inicializados aquí son usados por move_wasd.c y move_rotate.c.

La posición inicial se valida con validate_map.c para evitar colocar al jugador sobre espacios vacíos o paredes. */