/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:19:06 by sergio-jime       #+#    #+#             */
/*   Updated: 2025/11/27 13:04:16 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
