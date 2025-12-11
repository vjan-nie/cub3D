/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:41:44 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/11 13:30:53 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
* @brief Initiates the ray's variables for each column,
* which we will use to calculate and perform DDA.
* @param ray_offset It's the x normalized coordinate inside the camera plane.
* Defines an offset amount between the limits of the FOV 
* (range 1 to -1, being -1 full left, 0 center, and 1 full right).
* To calculate the current ray's direction, we start from the player's
* vision direction (center), and strafe it through the camera plane 
* (p->dir_x + p->plane_x) and (p->dir_y + p->plane_y).
* We then multiply the result with the offset, to rotate towards 
* the proper direction.
* @note There are security conditions to protect the rays from
* reaching outside the grid.
*/
static void	init_ray_vars(t_cub3d *cub, t_ray *r, int x)
{
	t_player	*p;
	double		ray_offset;

	p = &cub->player;
	ray_offset = 2.0 * x / (double)cub->screen_width - 1.0;
	r->dir_x = p->dir_x + p->plane_x * ray_offset;
	r->dir_y = p->dir_y + p->plane_y * ray_offset;
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	if (r->map_y < 0)
		r->map_y = 0;
	if (r->map_y >= cub->map.height)
		r->map_y = cub->map.height - 1;
	if (r->map_x < 0)
		r->map_x = 0;
	if (r->map_x >= (int)ft_strlen(cub->map.grid[r->map_y]))
		r->map_x = (int)ft_strlen(cub->map.grid[r->map_y]) - 1;
	calc_delta(r);
	calc_step_side(p, r);
}

/**
 * @brief Security check: if the ray excedes the map's limits,
 * consider it a hit.
 */
static bool	reaches_map_limit(t_cub3d *cub, t_ray *r)
{
	if (r->map_y < 0 || r->map_y >= cub->map.height)
	{
		r->hit = 1;
		return (1);
	}
	if (r->map_x < 0)
	{
		r->hit = 1;
		return (1);
	}
	if (r->map_x >= (int)ft_strlen(cub->map.grid[r->map_y]))
	{
		r->hit = 1;
		return (1);
	}
	if (cub->map.grid[r->map_y][r->map_x] == '1')
	{
		r->hit = 1;
		return (1);
	}
	return (0);
}

/**
* @brief DDA algorithm iteration: rays keep moving forward
* until they hit a wall or map limit.
*/
static void	perform_dda(t_cub3d *cub, t_ray *r)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (reaches_map_limit(cub, r))
			break ;
	}
}

/**
* @brief Draws the vertical wall line with the corresponding texture.
*/
static void	draw_wall_line_textured(t_cub3d *cub, t_ray *r, int x)
{
	t_img	*tex;
	int		y;
	int		tex_x;
	int		tex_y;
	char	*dst;

	tex = select_wall_texture(cub, r);
	tex_x = calc_wall_tex_x(cub, r, tex);
	tex_x = clamp(tex_x, 0, tex->width -1);
	y = r->start;
	while (y <= r->end)
	{
		tex_y = y * 256 - cub->screen_height * 128 + r->line_h * 128;
		tex_y = (tex_y * tex->height / r->line_h) / 256;
		tex_y = clamp(tex_y, 0, tex->height -1);
		dst = tex->data + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
		put_pixel(&cub->frame, x, y, ((unsigned char)dst[2] << 16) | \
			((unsigned char)dst[1] << 8) | (unsigned char)dst[0]);
		y++;
	}
}

/**
 * @brief The main raycasting loop.
 * Iterates through every vertical column of the screen to render the 3D scene.
 * @param cub Pointer to the main t_cub3d structure.
 * @details
 * The algorithm (DDA) follows these steps for each vertical strip (column):
 * 1. **Initialization:** Calculate ray direction and position.
 * 2. **Step Calculation:** Determine delta distances and initial side
 * distances.
 * 3. **DDA Execution:** Step through the grid until a wall is hit.
 * 4. **Projection:** Calculate the perpendicular distance (to avoid fish-eye)
 * and determining line height.
 * 5. **Rendering:** Select the texture and draw the vertical line.
 */
void	raycast(t_cub3d *cub)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < cub->screen_width)
	{
		init_ray_vars(cub, &r, x);
		perform_dda(cub, &r);
		calc_line_params(cub, &r);
		draw_wall_line_textured(cub, &r, x);
		x++;
	}
}
