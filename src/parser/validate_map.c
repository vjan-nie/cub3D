/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 10:05:52 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/29 20:09:17 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_map.c
 * @brief Core module for final validation of the map grid, checking character
 * validity, player position constraints, and map closure integrity.
 */
#include "cub3d.h"

/**
 * @brief Checks if a character is one of the allowed map symbols.
 * Valid characters include:
 * - '0': Walkable floor.
 * - '1': Wall.
 * - ' ': Empty space (used outside the defined area, typically converted to
 * '0' during normalization).
 * - 'N', 'S', 'E', 'W': Player starting position and orientation.
 * @param c The character to validate.
 * @return bool True if the character is valid, false otherwise.
 */
bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * @brief Validates constraints specific to the player starting tile.
 * This function checks for three main rules:
 * 1. Counts the number of players found so far (`*count`).
 * 2. Ensures the player count does not exceed one.
 * 3. Prevents the player from being placed on the outer edge (boundary)
 * of the map.
 * @param map Pointer to the t_map structure.
 * @param count Pointer to the running total of players found.
 * @param y The row index of the tile.
 * @param x The column index of the tile.
 * @return bool True if the tile is either not a player or is a valid player
 * placement, false on error.
 */
static bool	validate_player_tile(t_map *map, int *count, int y, int x)
{
	char	c;

	c = map->grid[y][x];
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

/**
 * @brief Checks if a walkable tile is safely contained within the
 * map boundaries.
 * For any non-wall tile ('0' or player start), this function enforces
 * the closure rule.
 * Specifically, it checks that the tile is not located on the physical
 * edge of the normalized grid (y=0, y=max-1, x=0, x=max-1).
 * @param map Pointer to the t_map structure.
 * @param y The row index of the tile.
 * @param x The column index of the tile.
 * @return bool True if the tile is a wall ('1') or is safely located away
 * from the map edges, false otherwise.
 */
static bool	is_surrounded_by_walls(t_map *map, int y, int x)
{
	if (map->grid[y][x] == '1')
		return (true);
	if (y == 0 || y == map->height - 1)
		return (false);
	if (x == 0 || x == map->width - 1)
		return (false);
	if (map->grid[y - 1][x] == '\0')
		return (false);
	if (map->grid[y + 1][x] == '\0')
		return (false);
	if (map->grid[y][x - 1] == '\0')
		return (false);
	if (map->grid[y][x + 1] == '\0')
		return (false);
	return (true);
}

/**
 * @brief Performs all necessary validations for a single tile (character).
 * Orchestrates the character check, player constraints, and map closure check.
 * @param map Pointer to the t_map structure.
 * @param count Pointer to the running total of players found.
 * @param y The row index of the tile.
 * @param x The column index of the tile.
 * @return bool True if the tile passes all validation rules, false otherwise.
 */
static bool	validate_tile(t_map *map, int *count, int y, int x)
{
	char	c;

	c = map->grid[y][x];
	if (!is_valid_char(c))
		return (ft_error("Invalid character in map\n"), false);
	if (!validate_player_tile(map, count, y, x))
		return (false);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!is_surrounded_by_walls(map, y, x))
			return (ft_error("Map is not closed\n"), false);
	}
	return (true);
}

/**
 * @brief Main function to validate the integrity and completeness of the
 * parsed map.
 * Iterates through every cell in the normalized map grid to ensure:
 * 1. All characters are valid.
 * 2. Walkable areas are properly closed (no tile touches the edge).
 * 3. Exactly one player starting position is present.
 * @param map Pointer to the t_map structure containing the normalized grid
 * and dimensions.
 * @return bool True if the map is valid and ready for raycasting,
 * false otherwise.
 */
bool	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	player_count;

	y = 0;
	player_count = 0;
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
		return (ft_error("Map must contain one player\n"), false);
	return (true);
}
