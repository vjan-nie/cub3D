/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:05:52 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/28 19:01:13 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** is_valid_char:
** Verifica si un carácter del mapa es válido:
** - '0': suelo donde el jugador puede caminar
** - '1': pared
** - ' ': espacio vacío
** - 'N', 'S', 'E', 'W': posición inicial del jugador y dirección
*/
bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		 || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}


/*
** validate_player_tile:
** Comprueba si la celda contiene al jugador:
** - Solo debe haber un jugador en el mapa.
** - No puede estar en los bordes del mapa.
*/
static bool	validate_player_tile(t_map *map, int *count, int y, int x)
{
	char	c = map->grid[y][x];

	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (true);

	(*count)++;
	if (*count > 1)
		return (ft_error("More than one player in the map\n"), false);

	if (y == 0 || y == map->height - 1)
		return (ft_error("Player on the edge of the map\n"), false);

	if (x == 0 || x == map->width - 1)
		return (ft_error("Player on the edge of the map\n"), false);

	return (true);
}


static bool	is_surrounded_by_walls(t_map *map, int y, int x)
{
	// 1. Si es pared, no hay nada que comprobar.
	if (map->grid[y][x] == '1')
		return true;

	// 2. Comprobaciones de límites (no debe estar en el borde)
	if (y == 0 || y == map->height - 1)
		return false;
	if (x == 0 || x == map->width - 1)
		return false;

	// 3. Vecinos: deben existir y no ser fuera del mapa
	if (map->grid[y - 1][x] == '\0')
		return false;
	if (map->grid[y + 1][x] == '\0')
		return false;
	if (map->grid[y][x - 1] == '\0')
		return false;
	if (map->grid[y][x + 1] == '\0')
		return false;

	// Si llegamos aquí, el tile está cerrado por algo:
	// 1 o 0 o jugador, y es válido.
	return true;
}

/*
** validate_tile:
** Valida cada celda individual:
** 1) Carácter válido.
** 2) Si es jugador, validar posición.
** 3) Si es un espacio caminable, asegurarse de que esté cerrado por paredes.
*/
static bool	validate_tile(t_map *map, int *count, int y, int x)
{
	char	c = map->grid[y][x];

	if (!is_valid_char(c))
		return (ft_error("Invalid character in map\n"), false);

	if (!validate_player_tile(map, count, y, x))
		return (false);

	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!is_surrounded_by_walls(map, y, x))
			return (ft_error("Map is not closed around a walkable tile\n"), false);
	}

	return (true);
}

/*
** validate_map:
** Valida el mapa completo:
** - Recorre todas las filas y columnas.
** - Valida cada celda individualmente.
** - Comprueba que haya exactamente un jugador.
*/
bool	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	player_count = 0;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!validate_tile(map, &player_count, y, x))
				return (false);
			x++;
		}
		y++;
	}

	if (player_count != 1)
		return (ft_error("Map must contain exactly one player\n"), false);

	return (true);
}
