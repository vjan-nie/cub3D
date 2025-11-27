/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:51:42 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 15:47:39 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_utils2.c
 * @brief Collection of utility functions for querying line properties and map
 * dimensions during parsing.
 * These functions help classify configuration lines and determine the required
 * size for the map grid normalization.
 */
#include "cub3d.h"

/**
 * @brief Calculates the length of the longest string within a 2D array
 * of strings.
 * This maximum length is used later to "normalize" the map, ensuring all rows
 * in the final grid have the same length (rectangular shape) by padding shorter
 * lines with spaces.
 * @param grid The 2D array of strings (the map grid or a subset thereof).
 * @return int The length of the longest string found in the array.
 */
int	get_max_line_length(char **grid)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/**
 * @brief Checks if a given line is effectively empty.
 * A line is considered empty if it is NULL, or if it consists solely of
 * space characters (' ') or tab characters ('\t'). This is vital for ignoring
 * gaps in the configuration section of the `.cub` file.
 * @param line The string (line) to check.
 * @return bool True if the line is empty or contains only whitespace,
 * false otherwise.
 */
bool	is_line_empty(const char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Identifies if a line starts with one of the four required texture
 * identifiers.
 * Checks specifically for "NO ", "SO ", "WE ", or "EA " at the beginning
 * of the line.
 * It only validates the identifier, not the path itself.
 * @param line The string (line) to check.
 * @return bool True if the line matches a texture identifier followed by a
 * space, false otherwise.
 */
bool	is_texture_line(const char *line)
{
	if (!line)
		return (false);
	if (!ft_strncmp(line, "NO ", 3))
		return (true);
	if (!ft_strncmp(line, "SO ", 3))
		return (true);
	if (!ft_strncmp(line, "WE ", 3))
		return (true);
	if (!ft_strncmp(line, "EA ", 3))
		return (true);
	return (false);
}

/**
 * @brief Identifies if a line starts with a floor ('F') or ceiling ('C')
 * color identifier.
 * Checks specifically for "F " or "C " at the beginning of the line.
 * It only validates the identifier, not the RGB format that follows.
 * @param line The string (line) to check.
 * @return bool True if the line matches a color identifier followed by a
 * space, false otherwise.
 */
bool	is_color_line(const char *line)
{
	if (!line)
		return (false);
	if (!ft_strncmp(line, "F ", 2))
		return (true);
	if (!ft_strncmp(line, "C ", 2))
		return (true);
	return (false);
}
