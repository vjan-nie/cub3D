/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:01:22 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/02 14:12:33 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Calculate the rotation movement for the
 * player's vision direction vector and the camera 
 * vector plane (perpendicular to the vision)
 */
static void	rotate_dir_plane(t_player *p, double rot)
{
	double	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	double old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

/**
 * @brief Calculate left rotation movement, using
 * the rotation negative value (radians per frame)
 */
void	rotate_left(t_cub3d *cub)
{
	t_player	*p;
	double		rot;

	p = &cub->player;
	rot = -p->rot_speed;
	rotate_dir_plane(p, rot);
}

/**
 * @brief Calculate right rotation movement, using
 * the rotation positive value (radians per frame)
 */
void	rotate_right(t_cub3d *cub)
{
	t_player	*p;
	double		rot;

	p = &cub->player;
	rot = p->rot_speed;
	rotate_dir_plane(p, rot);
}
