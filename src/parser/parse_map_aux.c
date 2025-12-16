/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:04:08 by sergio-jime       #+#    #+#             */
/*   Updated: 2025/12/16 18:29:33 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Auxiliary function to split and validate the format of a color line.
 * It ensures the line contains exactly the identifier and the RGB string,
 * preventing extra arguments.
 * @param line The raw configuration line from the .cub file.
 * @return char** The split array of strings on success, or NULL if the
 * format is invalid or contains too many elements.
 */
char	**parse_color_aux(const char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
	{
		ft_free_array(split);
		ft_error("Invalid color line\n");
		return (NULL);
	}
	if (split[2])
	{
		ft_free_array(split);
		ft_error("Too many rgb elements\n");
		return (NULL);
	}
	return (split);
}

/**
 * @brief Auxiliary function to split and validate the format of a texture line.
 * It checks that the line consists of exactly the identifier (NO, SO, WE, EA)
 * and the texture file path.
 * @param line The raw configuration line from the .cub file.
 * @return char** The split array of strings on success, or NULL if the
 * format is invalid or contains extra information.
 */
char	**parse_texture_aux(const char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
	{
		ft_free_array(split);
		ft_error("Invalid texture\n");
		return (NULL);
	}
	if (split[2])
	{
		ft_free_array(split);
		ft_error("Too many texture elements\n");
		return (NULL);
	}
	return (split);
}
