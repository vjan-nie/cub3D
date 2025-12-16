/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 08:10:11 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/16 14:15:57 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if the color code is in valid range:
 * [0,255]
 */
static bool	in_valid_range(const char *s)
{
	int	i;
	int	n;

	i = 0;
	if (!s || !*s)
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	n = ft_atoi(s);
	return (n >= 0 && n <= 255);
}

/**
 * @brief Converts an "R,G,B" string representation into a single 32-bit integer
 * color value (0x00RRGGBB).
 * This function validates the format, converts the components, and checks
 * the range.
 * @param str The RGB string (e.g., "255,0,128").
 * @return int The composite integer color value, or -1 on error.
 * @details
 * 1. Splits the input string by the comma delimiter (',').
 * 2. Requires exactly three resulting components (R, G, B).
 * 3. Converts each component to an integer using `ft_atoi`.
 * 4. **Memory Management**: The split array is freed using `ft_free_array`
 * regardless of success or failure.
 * 5. Validates that each R, G, B value is within the [0, 255] range.
 * 6. Combines the values using bitwise shifts: `(r << 16) | (g << 8) | b`.
 */
int	parse_rgb(const char *str)
{
	char	**p;
	int		r;
	int		g;
	int		b;

	p = ft_split(str, ',');
	if (!p || !p[0] || !p[1] || !p[2])
		return (ft_free_array(p), -1);
	if (p[3])
		return (ft_free_array(p), -1);
	if (!in_valid_range(p[0]) || !in_valid_range(p[1]) || !in_valid_range(p[2]))
		return (ft_free_array(p), -1);
	r = ft_atoi(p[0]);
	g = ft_atoi(p[1]);
	b = ft_atoi(p[2]);
	ft_free_array(p);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
