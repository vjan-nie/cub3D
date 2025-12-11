/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:03:18 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/11 13:24:50 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Frees the texture path strings stored in the map structure.
 * Iterates through the 4 cardinal directions (NO, SO, EA, WE) and frees
 * the string memory if it was allocated.
 * @param paths The array of strings containing the texture paths.
 * @note This only frees the path strings, not the MLX image pointers
 * (which are handled by the cleanup routine).
 */
void	free_textures(char **paths)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (paths[i])
			free(paths[i]);
		i++;
	}
}

/**
 * @brief Frees all dynamic memory associated with the map structure.
 * This includes:
 * - The map grid (2D array of characters).
 * - The texture path strings.
 * @param map Pointer to the t_map structure.
 * @note It does not modify floor/ceiling colors (stack integers) nor
 * MLX images (handled by cleanup_and_exit).
 */
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
	{
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	i = 0;
	while (i < 4)
	{
		if (map->tex_paths[i])
			free(map->tex_paths[i]);
		i++;
	}
}

/**
 * @brief Utility function to free the map and return NULL in one step.
 * Useful for cleaner error handling and return statements in the parser.
 * @param map Pointer to the t_map structure to be freed.
 * @return void* Always returns NULL.
 */
void	*free_map_return(t_map *map)
{
	free_map(map);
	return (NULL);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 * Commonly used to clean up the result of functions like ft_split.
 * @param array The NULL-terminated array of strings to free.
 */
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief Frees a partially allocated map grid upon failure.
 * Used during the parsing process if memory allocation fails mid-way
 * through copying the map lines.
 * @param map Pointer to the t_map structure.
 * @param filled The number of lines successfully allocated before
 * the error.
 * @return int Always returns 0.
 */
int	free_partial_grid(t_map *map, int filled)
{
	int	i;

	i = 0;
	while (i < filled)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	return (0);
}
