/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:04:04 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:39:58 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Actualiza la posición y orientación del jugador según las teclas presionadas
// Se llama normalmente en cada frame del juego
void	update_player(t_cub3d *cub)
{
	if (cub->key_code.w)       // Tecla W: mover hacia adelante
		move_forward(cub);
	if (cub->key_code.s)       // Tecla S: mover hacia atrás
		move_backward(cub);
	if (cub->key_code.a)       // Tecla A: moverse a la izquierda (strafe)
		move_left(cub);
	if (cub->key_code.d)       // Tecla D: moverse a la derecha (strafe)
		move_right(cub);
	if (cub->key_code.left)    // Flecha izquierda: rotar a la izquierda
		rotate_left(cub);
	if (cub->key_code.right)   // Flecha derecha: rotar a la derecha
		rotate_right(cub);
}

// Comprueba si un carácter representa la dirección inicial de un jugador
// Se usa para encontrar al jugador en el mapa
bool	is_player_direction(char c)
{
	if (c == 'N' || c == 'S') // Norte o Sur
		return (true);
	if (c == 'E' || c == 'W') // Este u Oeste
		return (true);
	return (false);
}

// Busca la posición inicial del jugador en el mapa y devuelve la dirección encontrada
// - px y py son punteros donde se almacenará la coordenada X e Y
// - Retorna 'N', 'S', 'E' o 'W' si encuentra al jugador, 0 si no lo encuentra
char	find_player_tile(t_map *map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_player_direction(map->grid[y][x])) // Se encontró la celda del jugador
			{
				*px = x;   // Guarda la coordenada X
				*py = y;   // Guarda la coordenada Y
				return (map->grid[y][x]); // Devuelve la dirección
			}
			x++;
		}
		y++;
	}
	return (0); // No se encontró jugador
}
