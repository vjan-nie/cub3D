/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_wasd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:00:28 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/16 13:09:23 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Forward movement calculation, using the player's vision direction
 * vector (dir_x, dir_y).
 */
void	move_forward(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, p->dir_x * speed, p->dir_y * speed);
}

/**
 * @brief Forward movement calculation, using the negative values of
 * the player's vision direction vector (dir_x, dir_y).
 */
void	move_backward(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, -p->dir_x * speed, -p->dir_y * speed);
}

/**
 * @brief Strafe left movement calculation, perpendicular to the player's
 * vision direction, which is the camera plane (- plane_x, - plane_y).
 */
void	move_left(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, p->plane_x * speed, p->plane_y * speed);
}

/**
 * @brief Strafe right movement calculation, perpendicular to the player's
 * vision direction, which is the camera plane (plane_x, plane_y)
 */
void	move_right(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, -p->plane_x * speed, -p->plane_y * speed);
}
