/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:01:08 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/02 13:41:06 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
