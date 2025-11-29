/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:11 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/29 17:39:36 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map.c
 * @brief Core module for reading, loading, and validating the .cub map file.
 * This file implements the primary parsing pipeline, including file reading,
 * configuration extraction, map data extraction, normalization, and validation.
 */
#include "../includes/cub3d.h"

/**
 * @brief Utility to check if a segment of the raw file content contains any
 * valid map tile.
 * It iterates from index 'start' up to (but not including) index 'i' in the
 * 'joined' string.
 * This is used by `check_map_block` to verify that a line (between line_start
 * and '\n') contains actual map data, not just whitespace.
 * @param i The end index (the newline character or end of string).
 * @param start The starting index of the line in the 'joined' string.
 * @param joined The single string containing the entire file content.
 * @return bool True if at least one valid tile character is found,
 * false otherwise.
 * @note Relies on `is_valid_char` to classify map characters.
 */
static bool	check_map_aux(int i, int start, const char *joined)
{
	int	j;

	j = start;
	while (j < i)
	{
		if (is_valid_char(joined[j]))
			return (true);
		j++;
	}
	return (false);
}

/**
 * @brief Validates the map data block integrity, preventing empty lines
 * within the map definition.
 * Iterates through the raw content from the point where the map
 * started (`start`).
 * It ensures that every line found after the map begins contains at least
 * one valid map character ('0', '1', 'N', 'S', 'E', 'W', ' '). Empty lines
 * are forbidden between the first and last line of the map block.
 * @param joined The single string containing the entire file content.
 * @param start The index in `joined` where the map block begins.
 * @return bool True if the map block has no empty lines, false and prints
 * error otherwise.
 */
static bool	check_map_block(const char *joined, int start)
{
	int		i;
	int		line_start;
	bool	has_tile;

	i = start;
	line_start = start;
	while (joined[i])
	{
		if (joined[i] == '\n' || joined[i + 1] == '\0')
		{
			has_tile = check_map_aux(i, line_start, joined);
			if (!has_tile)
				return (ft_error("Empty lines inside map\n"), false);
			line_start = i + 1;
		}
		i++;
	}
	return (true);
}

/**
 * @brief Reads the file line by line, concatenates all content, and
 * validates map block continuity.
 * This function handles the file reading and accumulation into one large
 * string. Crucially, it identifies when the map block starts (`map_start`)
 * and, after EOF, calls `check_map_block` to enforce the rule that no empty
 * lines are allowed within the map definition.
 * @param fd The open file descriptor of the .cub file.
 * @param joined The initial allocated string to accumulate the content.
 * @return char* The resulting single string containing the entire file content,
 * or NULL on memory allocation failure or if empty lines are found in the
 * map block.
 */
static	char	*accumulate_gnl(int fd, char *joined)
{
	int		map_start;
	char	*line;
	char	*tmp;

	map_start = -1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map_start == -1 && !is_texture_line(line)
			&& !is_color_line(line) && !is_line_empty(line))
			if (in_map(line))
				map_start = ft_strlen(joined);
		tmp = ft_strjoin(joined, line);
		free(line);
		if (!tmp)
			return (free(joined), NULL);
		free(joined);
		joined = tmp;
		line = get_next_line(fd);
	}
	if (map_start >= 0 && !check_map_block(joined, map_start))
		return (free(joined), NULL);
	return (joined);
}

/**
 * @brief Reads the entire content of the .cub file and returns it as an
 * array of strings.
 * This function handles file checking, opening, reading (via `accumulate_gnl`),
 * and initial data structuring (via `ft_split`).
 * @param path The path to the .cub map file.
 * @return char** An array of strings where each element is a line from the
 * file, or NULL on any failure during file handling, GNL, or pre-validation.
 * @details
 * 1. Checks file extension via `check_extension`.
 * 2. Opens the file.
 * 3. Accumulates all content into one large string using `accumulate_gnl`.
 * 4. Closes the file.
 * 5. Splits the large string by the newline character `\n` using `ft_split`
 * to create the final array.
 * 6. Handles various errors with corresponding cleanup.
 */
static char	**read_file_lines(const char *path)
{
	int		fd;
	char	*joined;
	char	**lines;

	if (!check_extension(path))
		return (ft_error("Invalid file extension\n"), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Cannot open file\n"), NULL);
	joined = ft_strdup("");
	if (!joined)
		return (close(fd), ft_error("Malloc failed\n"), NULL);
	joined = accumulate_gnl(fd, joined);
	close(fd);
	if (!joined)
		return (NULL);
	lines = ft_split(joined, '\n');
	free(joined);
	if (!lines)
		return (ft_error("Failed to split lines\n"), NULL);
	return (lines);
}

/**
 * @brief Coordinates the entire map loading and validation pipeline.
 * This is the main function for the parsing stage, orchestrating five key
 * steps to process the raw file data into a validated, playable map structure.
 * @param map Pointer to the t_map structure where configuration and grid data
 * will be stored.
 * @param path The path to the .cub map file.
 * @return bool True if the map is loaded, configured, and validated
 * successfully, false otherwise.
 * @details The parsing pipeline steps are:
 * 1. **read_file_lines**: Get the raw content as an array of lines.
 * 2. **parse_config**: Extract texture paths (NO, SO, WE, EA) and
 * floor/ceiling colors.
 * 3. **parse_map**: Extract the raw 2D map grid from the file lines.
 * 4. **normalize_map**: Pad the map grid to a rectangular shape. 
 * 5. **validate_map**: Check for map closure (walls), valid characters, and
 * unique player starting position.
 */
bool	load_and_validate_map(t_map *map, const char *path)
{
	char	**file_lines;

	file_lines = read_file_lines(path);
	if (!file_lines)
		return (false);
	if (!parse_config(map, file_lines))
		return (ft_free_array(file_lines), false);
	if (!parse_map(map, file_lines))
		return (ft_free_array(file_lines), false);
	normalize_map(map);
	if (!validate_map(map))
		return (ft_free_array(file_lines), false);
	ft_free_array(file_lines);
	return (true);
}
