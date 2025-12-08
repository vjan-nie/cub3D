/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:31:50 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/08 07:48:14 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file normalize_map.c
 * @brief Functions for ensuring the map grid is perfectly rectangular and
 * standardizing internal characters.
 * This process is crucial for preventing segmentation faults during boundary
 * checks in the raycasting loop.
 */
#include "cub3d.h"

/**
 * @brief Pads a single map line with spaces until it reaches the
 * specified width.
 * If the source line is shorter than `width`, a new string is allocated,
 * the content is copied, the remainder is filled with spaces (' '), and the
 * original string is freed.
 * If the line is already long enough, it is returned unchanged.
 * @param src The map line string to pad.
 * @param width The target width (maximum line length in the map).
 * @return char* The newly padded string (dynamically allocated), or NULL on
 * malloc failure.
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
		return (ft_error("Malloc failed\n"), free(src), NULL);
	ft_memcpy(dst, src, len);
	ft_memset(dst + len, ' ', width - len);
	dst[width] = '\0';
	free(src);
	return (dst);
}

/**
 * @brief Ensures the map grid is rectangular and standardizes
 * internal/padded characters.
 * This function performs two main tasks:
 * 1. **Rectangular Padding**: Determines the maximum line length and pads
 * all shorter lines with spaces (' ') using `pad_line` to achieve a uniform
 * rectangular shape of `map->height` by `map->width`.
 * 2. **Character Standardization**: Iterates through the rectangular grid and
 * replaces every space character (' ') with a floor tile character ('0').
 * This ensures that all padded areas and internal map spaces are treated as
 * walkable floor tiles for subsequent validation and rendering.
 * @param map Pointer to the t_map structure containing the map grid.
 * @details The process modifies the `map->grid` lines in place, potentially
 * reallocating them via `pad_line`. The `map->width` is updated to the
 * new maximum (normalized) width.
 */
void	normalize_map(t_map *map)
{
	int	x;
	int	y;
	int	max;

	max = get_max_line_length(map->grid);
	map->width = max;
	y = 0;
	while (map->grid[y])
	{
		map->grid[y] = pad_line(map->grid[y], max);
		y++;
	}
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == ' ')
				map->grid[y][x] = '1';
			x++;
		}
		y++;
	}
}
