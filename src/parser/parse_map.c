/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:58:26 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:25:23 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** skip_config:
** Avanza por las líneas del archivo .cub mientras sean:
** - líneas de textura (NO, SO, WE, EA)
** - líneas de color (F, C)
** - líneas vacías
**
** Devuelve el índice de la primera línea que ya no es configuración,
** es decir, donde comienza el mapa.
*/
static int	skip_config(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_texture_line(lines[i])
			|| is_color_line(lines[i])
			|| is_line_empty(lines[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

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
			return (0);
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
	map->grid = malloc(sizeof(char *) * (h + 1));
	if (!map->grid)
		return (false);
	if (!copy_map_lines(map, lines, start, h))
		return (false);
	map->height = h;
	map->width = get_max_line_length(map->grid);
	return (true);
}
