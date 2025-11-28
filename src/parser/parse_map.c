/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:58:26 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/28 18:13:34 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** count_map_lines:
** Cuenta cuántas líneas tiene el mapa desde 'start' hasta el final
*/
static int	count_map_lines(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i])
		i++;
	return (i - start);
}

/*
** copy_map_lines:
** Copia las líneas del mapa al grid de t_map.
**
** Cada línea se duplica para que el map tenga su propio bloque de memoria.
** Devuelve 1 si todo salió bien, 0 si alguna strdup falló.
*/
static int	copy_map_lines(t_map *map, char **lines, int start, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		map->grid[i] = ft_strdup(lines[start + i]);
		if (!map->grid[i])
		{
			while (i < 0)
			{
				free(map->grid[i - 1]);
				i--;
			}
			return (free(map->grid), 0);
		}
		i++;
	}
	map->grid[h] = NULL;
	return (1);
}

/*
** parse_map:
** Función principal para cargar el mapa en memoria:
** 1) Saltamos las líneas de configuración.
** 2) Contamos cuántas líneas tiene el mapa.
** 3) Reservamos memoria para map->grid.
** 4) Copiamos las líneas al grid.
** 5) Guardamos altura y ancho máximo del mapa.
**
** Devuelve true si todo salió bien.
*/
bool	parse_map(t_map *map, char **lines)
{
	int	start;
	int	h;

	start = skip_config(lines);
	h = count_map_lines(lines, start);
	if (h <= 0)
		return (ft_error("Empty map\n"), false);
	map->grid = malloc(sizeof(char *) * (h + 1));
	if (!map->grid)
		return (false);
	if (!copy_map_lines(map, lines, start, h))
		return (false);
	map->height = h;
	map->width = get_max_line_length(map->grid);
	return (true);
}
