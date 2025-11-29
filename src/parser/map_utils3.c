/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:19:06 by sergio-jime       #+#    #+#             */
/*   Updated: 2025/11/29 17:42:31 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_utils3.c
 * @brief Utility function collection for map parsing.
 */
#include "../includes/cub3d.h"

/**
 * @brief Checks if the provided file path has the required ".cub" extension.
 * This function validates the input argument to ensure it points to a file
 * with the correct extension, a prerequisite for parsing.
 * @param path The string representing the file path.
 * @return bool True if the path is not NULL, is long enough, and ends exactly
 * with ".cub", false otherwise.
 * @details The check is performed by:
 * 1. Ensuring the path is not NULL.
 * 2. Ensuring the path length is at least 4 characters long (e.g., "a.cub").
 * 3. Using `ft_strnstr` to verify that the last four characters are
 * exactly ".cub".
 */
bool	check_extension(const char *path)
{
	int	len;

	if (!path)
		return (false);
	len = ft_strlen(path);
	if (len < 4)
		return (false);
	if (ft_strnstr(path + (len - 4), ".cub", 4) == NULL)
		return (false);
	return (true);
}

/**
 * @brief Finds the starting line index of the map grid within the file
 * lines array.
 * Iterates through the lines array, skipping lines that are:
 * - Valid texture configurations (NO, SO, WE, EA).
 * - Valid color configurations (F, C).
 * - Empty/whitespace-only lines.
 * @param lines The array of strings read from the .cub file.
 * @return int The index of the first line that is neither a configuration
 * nor empty.
 * This index is presumed to be the start of the map block. If no such line
 * is found, it returns the length of the array.
 */
int	skip_config(char **lines)
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

/**
 * @brief Checks if a line contains any valid map tile characters.
 * Used during file reading to determine when the configuration block ends and
 * the map block begins, or to enforce the rule that lines inside the map
 * block must contain map data.
 * @param line The string (line) to check.
 * @return bool True if the line contains at least one character classified as
 * a valid map tile, false otherwise.
 * @note Relies on the external utility `is_valid_char` to classify
 * map characters.
 */
bool	in_map(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_valid_char(line[i]))
			return (true);
		i++;
	}
	return (false);
}
