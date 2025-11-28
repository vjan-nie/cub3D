/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:19:06 by sergio-jime       #+#    #+#             */
/*   Updated: 2025/11/28 19:00:52 by sergio-jime      ###   ########.fr       */
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

/*
** skip_config:
** Avanza por las líneas del archivo .cub mientras sean:
** - líneas de textura (NO, SO, WE, EA)
** - líneas de color (F, C)
** - líneas vacías
**
** Devuelve el índice de la primera línea que ya no es configuración,
** es decir, donde comienza el mapa.
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
