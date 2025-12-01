/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:58:26 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/29 19:22:08 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_map.c
 * @brief Functions for extracting the map grid from the raw file lines into
 * the t_map structure.
 * Handles the calculation of map dimensions, memory allocation for the grid,
 * and copying the map data.
 */
#include "cub3d.h"

/**
 * @brief Calculates the number of lines corresponding to the map block.
 * Counts the number of strings in the array `lines` starting from the `start`
 * index up to the NULL terminator, effectively determining the height of the
 * raw map.
 * @param lines The array of all strings read from the .cub file.
 * @param start The index where the map block begins (returned by `skip_config`).
 * @return int The total number of map lines (the map height).
 */
static int	count_map_lines(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i])
		i++;
	return (i - start);
}

/**
 * @brief Copies the map lines from the file array to the allocated map grid
 * structure.
 * Iterates through the raw lines starting from `start` and uses `ft_strdup`
 * to create a deep copy of each line into `map->grid`. The array is
 * NULL-terminated.
 * @param map Pointer to the t_map structure containing the allocated `grid`.
 * @param lines The array of all strings read from the .cub file.
 * @param start The starting index of the map block in `lines`.
 * @param h The height (number of lines) of the map.
 * @return int 1 on success, 0 on failure (memory allocation error).
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
			while (i > 0)
			{
				i--;
				free(map->grid[i]);
			}
			return (free(map->grid), 0);
		}
		i++;
	}
	map->grid[h] = NULL;
	return (1);
}

/**
 * @brief Main function to extract and load the map grid into the
 * t_map structure.
 * Orchestrates the process of identifying the map block, calculating
 * its size, allocating memory, and copying the data.
 * @param map Pointer to the t_map structure.
 * @param lines The array of all strings read from the .cub file.
 * @return bool True if the map is successfully extracted and loaded,
 * false otherwise.
 * @details
 * 1. **`skip_config`**: Finds the starting index of the map block.
 * 2. **`count_map_lines`**: Calculates the map height (`h`).
 * 3. **Validation**: Checks if `h` is greater than 0 (non-empty map).
 * 4. **Allocation**: Allocates memory for `map->grid`.
 * 5. **`copy_map_lines`**: Performs the deep copy of the map data.
 * 6. **Dimension Assignment**: Sets `map->height` and `map->width`.
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
		return (ft_error("Malloc failed\n"), false);
	if (!copy_map_lines(map, lines, start, h))
		return (ft_error("Failed copy lines\n"), false);
	map->height = h;
	map->width = get_max_line_length(map->grid);
	return (true);
}
