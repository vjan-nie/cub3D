/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:11 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 13:04:41 by sergio-jime      ###   ########.fr       */
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
 * @brief Reads the file descriptor line by line and concatenates all content
 * into a single string.
 * Uses `get_next_line` (gnl) to read and append each line to the
 * `joined` string.
 * It ensures proper memory management by freeing the temporary `line` and the
 * old `joined` string in each iteration.
 * @param fd The open file descriptor of the .cub file.
 * @param joined The initial allocated string to accumulate the content.
 * @return char* The resulting single string containing the entire file content,
 * or NULL on memory allocation failure.
 */
static char	*accumulate_gnl(int fd, char *joined)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	while (!line)
	{
		tmp = ft_strjoin(joined, line);
		free(line);
		if (!tmp)
			return (free(joined), NULL);
		free(joined);
		joined = tmp;
		line = get_next_line(fd);
	}
	return (joined);
}

/**
 * @brief Reads the entire content of the .cub file and returns it as an array
 * of strings (lines).
 * This function handles file checking, opening, reading, and initial
 * data structuring.
 * @param path The path to the .cub map file.
 * @return char** An array of strings where each element is a line from the file,
 * or NULL on any failure.
 * @details
 * 1. Checks file extension via `check_extension`.
 * 2. Opens the file.
 * 3. Accumulates all content into one large string using `accumulate_gnl`.
 * 4. Closes the file.
 * 5. Splits the large string by the newline character `\n` using `ft_split`
 * to create the final array.
 * 6. Handles various errors (open failure, GNL error, empty file, split failure)
 * with corresponding cleanup.
 */
static char	**read_file_lines(const char *path)
{
	int		fd;
	char	**lines;
	char	*joined;

	if (!check_extension(path))
		return (ft_error("Invalid file extension\n"), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Cannot open file\n"), NULL);
	joined = ft_strdup("");
	if (!joined)
		return (close(fd), ft_error("Malloc error\n"), NULL);
	joined = accumulate_gnl(fd, joined);
	if (!joined)
		return (close(fd), ft_error("GNL error\n"), NULL);
	close(fd);
	if (joined[0] == '\0')
		return (free(joined), ft_error("File is empty\n"), NULL);
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
