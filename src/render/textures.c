/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:01:08 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/04 09:58:26 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
* @brief Gets the corresponding texture depending on the
* ray's direction and the wall side (0-North, 1-South, 2-West, 3-East)
* @note r->side refers to which kind of wall did the ray hit:
* 0: vertical (x)
* 1: horizontal (y)
*/
t_img	*select_wall_texture(t_cub3d *cub, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->step_x < 0)
			return (&cub->textures[0]);
		return (&cub->textures[1]);
	}
	else
	{
		if (r->step_y < 0)
			return (&cub->textures[2]);
		return (&cub->textures[3]);
	}
}

/**
* @brief Calculates the x axis coordinate of the texture.
*/
int	calc_wall_tex_x(t_cub3d *cub, t_ray *r, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = cub->player.y + r->perp * r->dir_y;
	else
		wall_x = cub->player.x + r->perp * r->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

/**
 * @brief Loads one texture from an .xpm file using
 * MLX's image loader. Updates data on t_img structure,
 * which is the frame buffer.
 */
static bool	load_one_texture(t_cub3d *cub, t_img *tex, char *path)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	tex->img_ptr = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!tex->img_ptr)
		return (ft_error("Failed to load XPM texture\n"), false);
	tex->width = width;
	tex->height = height;
	tex->data = mlx_get_data_addr(tex->img_ptr,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->data)
		return (ft_error("Failed to get texture data\n"), false);
	return (true);
}

/**
 * @brief Checks if there is a valid path to find the wall textures.
 */
static bool	check_paths(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->tex_paths[i])
			return (ft_error("Missing texture path\n"), false);
		i++;
	}
	return (true);
}

/**
 * @brief Loads wall textures from the given map file paths.
 */
bool	load_textures(t_cub3d *cub)
{
	int	i;

	if (!check_paths(&cub->map))
		return (false);
	i = 0;
	while (i < 4)
	{
		if (!load_one_texture(cub, &cub->textures[i], cub->map.tex_paths[i]))
			return (false);
		i++;
	}
	return (true);
}
