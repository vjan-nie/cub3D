/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:23 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/04 10:03:02 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
* @brief Calculates relative distance from the ray 
* till the next grid line (x and y).
* @param delta_x and @param delta_y represent the 
* distance that the ray needs to cross the line.
* It accumulates full distance in each iteration.
* @note fabs is used to avoid negative value, 
* and 1e30 to avoid divisions by zero.
*/
void	calc_delta(t_ray *r)
{
	if (r->dir_x == 0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->dir_x);
	if (r->dir_y == 0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->dir_y);
}

/**
* @brief Calculates the distance to the next grid line, and it's direction:
* step_x/step_y = direction in (+1 o -1)
* side_x/side_y = distancia que falta para llegar al próximo borde de celda
*/
void	calc_step_side(t_player *p, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (p->x - r->map_x);
		if (r->side_x < 1e-6)
			r->side_x = 1e-6;
		r->side_x *= r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - p->x);
		if (r->side_x < 1e-6)
			r->side_x = 1e-6;
		r->side_x *= r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (p->y - r->map_y);
		if (r->side_y < 1e-6)
			r->side_y = 1e-6;
		r->side_y *= r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - p->y);
		if (r->side_y < 1e-6)
			r->side_y = 1e-6;
		r->side_y *= r->delta_y;
	}
}

/**
* @brief Claculates the line to be drawn and the side of the wall in which
* the ray hits, using the perpendicular distance (to avoid fish-eye).
* We also clamp values to avoid extremely big numbers, or division by zero.
*/
void	calc_line_params(t_cub3d *cub, t_ray *r)
{
	if (r->side == 0)
		r->perp = (r->map_x - cub->player.x + (1 - r->step_x) / 2) / r->dir_x;
	else
		r->perp = (r->map_y - cub->player.y + (1 - r->step_y) / 2) / r->dir_y;
	if (r->perp <= 0.0)
		r->perp = 0.0001;
	r->line_h = (int)(cub->screen_height / r->perp);
	if (r->line_h > cub->screen_height * 10)
		r->line_h = cub->screen_height * 10;
	r->start = -r->line_h / 2 + cub->screen_height / 2;
	if (r->start < 0)
		r->start = 0;
	r->end = r->line_h / 2 + cub->screen_height / 2;
	if (r->end >= cub->screen_height)
		r->end = cub->screen_height - 1;
}
