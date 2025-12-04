/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:46:20 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/04 09:39:51 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gets the player initial position and direction 
 * (N, S, E, or W) in the map.
 * @note Adds 0.5 to each coordinate to keep the initial 
 * position in the center of the tile. This keeps the initial 
 * position from starting in the exact corner of the tile, 
 * triggering instant colision.
 */
static char	get_player_dir(t_map *map, t_player *p)
{
	int		px;
	int		py;
	char	dir;

	px = 0;
	py = 0;
	dir = find_player_tile(map, &px, &py);
	p->x = px + 0.5;
	p->y = py + 0.5;
	return (dir);
}

static void	set_dir(t_player *p, double dx, double dy)
{
	p->dir_x = dx;
	p->dir_y = dy;
}

static void	set_plane(t_player *p, double px, double py)
{
	p->plane_x = px;
	p->plane_y = py;
}

/**
 * @brief Sets player direction and camera plane accordingly to the 
 * initial position and direction defined in the map file.
 * Values to set: direction (dx, dy) and camera plane (px, py).
 * @note 0.66 is the default FOV angle in radians (which are defined by length), 
 * so 0.66 has to be the length of our perpendicular plane. That's what we need 
 * to add or take from x and y depending on the starting point.
 */
static void	set_dir_and_plane(t_player *p, char dir)
{
	if (dir == 'N')
	{
		set_dir(p, 0, -1);
		set_plane(p, FOV_ANGLE, 0);
	}
	else if (dir == 'S')
	{
		set_dir(p, 0, 1);
		set_plane(p, -FOV_ANGLE, 0);
	}
	else if (dir == 'E')
	{
		set_dir(p, 1, 0);
		set_plane(p, 0, FOV_ANGLE);
	}
	else if (dir == 'W')
	{
		set_dir(p, -1, 0);
		set_plane(p, 0, -FOV_ANGLE);
	}
}

/**
 * @brief Initialization of the player structure values.
 * Sets initial position and direction according to the map file info.
 * Sets default speed values, and sets player direction and camera plane
 * vectors accordingly to the initial position and direction.
 */
void	init_player(t_player *p, t_map *map)
{
	char	dir;

	dir = get_player_dir(map, p);
	p->move_speed = MOVEMENT_SPEED;
	p->rot_speed = ROTATION_SPEED;
	set_dir_and_plane(p, dir);
}
