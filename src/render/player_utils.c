/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:04:04 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/03 10:52:57 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks for accumulated keybord input related to the movement in every loop.
 * If any of the key codes realted to movement have been pressed (with the value 'true'),
 * we initiate the attempt to update the position and direction.
 */
void	update_player(t_cub3d *cub)
{
	if (cub->key_code.w)
		move_forward(cub);
	if (cub->key_code.s)
		move_backward(cub);
	if (cub->key_code.a)
		move_left(cub);
	if (cub->key_code.d)
		move_right(cub);
	if (cub->key_code.left)
		rotate_left(cub);
	if (cub->key_code.right)
		rotate_right(cub);
}

/**
 * @brief Checks for the player tile, which can only be one
 * of the valid chars which represent the direction (N, S, E, W).
 */
bool	is_player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

/**
 * @brief Searchs for the player tile in the map, updates the values of
 * the coordinates and returns a char which refers to the direction 
 * that the player should be looking at the begining. Return '0' if the 
 * player is not found.
 */
char	find_player_tile(t_map *map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_player_direction(map->grid[y][x]))
			{
				*px = x;
				*py = y;
				return (map->grid[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}
