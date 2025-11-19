/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:31:50 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:23:05 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** pad_line:
** Recibe una línea del mapa y un ancho deseado.
** Si la línea ya es suficientemente larga, la devuelve igual.
**
** Si es más corta:
** - crea una nueva string del tamaño exacto
** - copia el contenido original
** - rellena lo que falta con espacios
** - libera la original
**
** ¿Por qué espacios?  
** Porque en el mapa, un espacio es un “hueco”, así que
** visualmente no afecta pero mantiene la matriz consistente.
*/
static char	*pad_line(char *src, int width)
{
	int		len;
	char	*dst;

	len = ft_strlen(src);
	if (len >= width)
		return (src);
	dst = malloc(width + 1);
	if (!dst)
		return (src); // fallback silencioso si malloc falla
	ft_memcpy(dst, src, len);
	ft_memset(dst + len, ' ', width - len);
	dst[width] = '\0';
	free(src);
	return (dst);
}

/*
** normalize_map:
** Esta función hace el mapa rectangular.
**
** Pasos:
** 1) Calcula la longitud de la línea más larga.
** 2) Guarda ese ancho en map->width.
** 3) Rellena TODAS las demás líneas con espacios hasta ese ancho.
**
** Esto soluciona problemas típicos como:
** - rayos que se salen de la matriz
** - mapas hechos a mano con líneas irregulares
** - tener que comprobar strlen en cada acceso
*/
void	normalize_map(t_map *map)
{
	int	y;
	int	max;

	y = 0;
	max = get_max_line_length(map->grid);
	map->width = max;
	while (map->grid[y])
	{
		map->grid[y] = pad_line(map->grid[y], max);
		y++;
	}
}

