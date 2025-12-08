/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:55:46 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/08 08:13:33 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_map_utils.c
 * @brief Utility functions for parsing and validating map configuration
 * entries (colors and textures).
 */
#include "cub3d.h"

/**
 * @brief Parses a floor ('F') or ceiling ('C') color line and stores
 * the integer RGB value.
 * Checks for correct formatting, validates the RGB components, and ensures
 * no duplicate color entries exist.
 * @param map Pointer to the t_map structure.
 * @param line The configuration line.
 * @return bool True on success, false on error.
 */
static bool	parse_color(t_map *map, const char *line)
{
	char	**split;
	int		color;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_free_array(split), ft_error("Invalid color line\n"), false);
	color = parse_rgb(split[1]);
	if (color == -1)
		return (ft_free_array(split), ft_error("Invalid RGB values\n"), false);
	if (!ft_strncmp(split[0], "F", 2))
	{
		if (map->floor_color != 0)
			return (ft_free_array(split), ft_error("Duplicate floor\n"), false);
		map->floor_color = color;
	}
	else if (!ft_strncmp(split[0], "C", 2))
	{
		if (map->ceiling_color != 0)
			return (ft_free_array(split), ft_error("Duplicate ceil\n"), false);
		map->ceiling_color = color;
	}
	else
		return (ft_free_array(split), ft_error("Unknown color type\n"), false);
	ft_free_array(split);
	return (true);
}

/**
 * @brief Parses a texture configuration line (NO, SO, WE, EA) and stores
 * the file path.
 * Saves a dynamically allocated copy of the path string into the correct index
 * of `map->tex_paths`.
 * @param map Pointer to the t_map structure.
 * @param line The configuration line.
 * @return bool True on success, false on error.
 * @details
 * 1. Splits the line by space (' ') to separate the identifier (NO/SO/WE/EA)
 * from the path.
 * 2. Maps the identifier to the corresponding integer index (0-3).
 * 3. Checks for duplicate configuration (`map->tex_paths[index] != NULL`).
 * 4. **Memory Management**: Uses `ft_strdup` to allocate and store a persistent
 * copy of the file path. This allocated memory must be freed later
 * by `free_map`.
 * 5. The temporary split array is freed using `ft_free_array` before returning.
 */
static bool	parse_texture(t_map *map, const char *line)
{
	char	**split;
	int		index;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_free_array(split), ft_error("Invalid texture\n"), false);
	index = -1;
	if (!ft_strncmp(split[0], "NO", 3))
		index = 0;
	else if (!ft_strncmp(split[0], "SO", 3))
		index = 1;
	else if (!ft_strncmp(split[0], "WE", 3))
		index = 2;
	else if (!ft_strncmp(split[0], "EA", 3))
		index = 3;
	if (index == -1)
		return (ft_free_array(split), ft_error("Unknown texture\n"), false);
	if (map->tex_paths[index] != NULL)
		return (ft_free_array(split), ft_error("Duplicate texture\n"), false);
	map->tex_paths[index] = ft_strdup(split[1]);
	if (!map->tex_paths[index])
		return (ft_free_array(split), ft_error("Malloc error\n"), false);
	ft_free_array(split);
	return (true);
}

/**
 * @brief Auxiliary function that iterates through the raw file lines and
 * attempts to parse configuration entries.
 * It checks for texture, color, and empty lines, delegating the parsing work
 * and counting successful entries.
 * @param map Pointer to the t_map structure.
 * @param lines Array of strings containing all lines from the .cub file.
 * @param parsed The initial count of items already parsed.
 * @return int The total number of valid configuration items found
 * (4 textures + 2 colors = 6), or 0 on error.
 */
static int	parse_config_aux(t_map *map, char **lines, int parsed)
{
	int	i;

	i = 0;
	while (lines[i] && parsed < 6)
	{
		if (is_texture_line(lines[i]))
		{
			if (!parse_texture(map, lines[i]))
				return (false);
			parsed++;
		}
		else if (is_color_line(lines[i]))
		{
			if (!parse_color(map, lines[i]))
				return (false);
			parsed++;
		}
		else if (!is_line_empty(lines[i]))
			return (ft_error("Invalid config line\n"), false);
		i++;
	}
	return (parsed);
}

/**
 * @brief Main function for parsing the 6 configuration elements
 * (4 textures, 2 colors).
 * Ensures that exactly six unique and valid configuration items are
 * present at the beginning of the file.
 * @param map Pointer to the t_map structure where configuration data is stored.
 * @param lines Array of strings containing all lines from the .cub file.
 * @return bool True if exactly 6 configurations are successfully parsed,
 * false otherwise.
 * @note This function relies on `parse_config_aux` to find and count the
 * configuration lines.
 */
bool	parse_config(t_map *map, char **lines)
{
	int	parsed;

	parsed = 0;
	parsed = parse_config_aux(map, lines, parsed);
	if (parsed != 6)
		return (ft_error("Missing config entries\n"), false);
	return (true);
}
