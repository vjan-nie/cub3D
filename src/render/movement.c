/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:47:14 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/02 13:51:27 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if the attempted movement result is
 * valid.
 */
static bool	is_walkable(char c)
{
	if (c == '0')
		return (true);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}


/**
 * @brief Checks for movement attempts accumulated by keyboard input,
 * calculates result and, if it's a valid movement, updates the 
 * player's position.
 */
void	check_and_move(t_cub3d *cub, double mx, double my)
{
	t_player	*p;
	int			next_x;
	int			next_y;

	p = &cub->player;
	next_x = (int)(p->x + mx);
	next_y = (int)(p->y + my);
	if (is_walkable(cub->map.grid[(int)p->y][next_x]))
		p->x += mx;
	if (is_walkable(cub->map.grid[next_y][(int)p->x]))
		p->y += my;
}
