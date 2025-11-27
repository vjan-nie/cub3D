/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 01:20:38 by sergio-jime       #+#    #+#             */
/*   Updated: 2025/11/27 02:37:02 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cleaner.c
 * @brief Functions responsible for safely destroying MLX resources and
 * freeing dynamic memory.
 * This module ensures a clean shutdown of the application by checking the state
 * of all allocated pointers (MLX image pointers, window pointer, and map
 * memory) before attempting to destroy or free them, preventing segfaults on
 * error paths.
 */
#include "cub3d.h"

/**
 * @brief Destroys the MiniLibX connection and frees the MLX handler pointer.
 * This must be the last MiniLibX-related operation, as all other MLX destroy
 * functions rely on a valid `cub->mlx` pointer.
 * @param cub Pointer to the main t_cub3d context structure.
 */
static void	clean_mlx(t_cub3d *cub)
{
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
}

/**
 * @brief Destroys all four texture images (NO, SO, WE, EA) if they were loaded.
 * Iterates through the `cub->textures` array and destroys any valid image
 * pointer using `mlx_destroy_image`.
 * @param cub Pointer to the main t_cub3d context structure.
 * @note Relies on `cub->mlx` being valid.
 */
static void	clean_textures(t_cub3d *cub)
{
	size_t	i;

	i = 0;
	if (cub->mlx)
	{
		while (i < 4)
		{
			if (cub->textures[i].img_ptr)
			{
				mlx_destroy_image(cub->mlx, cub->textures[i].img_ptr);
				cub->textures[i].img_ptr = NULL;
			}
			i++;
		}
	}
}

/**
 * @brief Destroys the main MiniLibX window.
 * Checks if both the MLX handler and the window pointer are valid
 * before destruction.
 * @param cub Pointer to the main t_cub3d context structure.
 * @note Relies on `cub->mlx` being valid.
 */
static void	clean_window(t_cub3d *cub)
{
	if (cub->mlx && cub->win)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		cub->win = NULL;
	}
}

/**
 * @brief Destroys the main framebuffer image (`cub->frame`).
 * This image is the one used for the rendering loop and must
 * be destroyed before closing the MLX connection.
 * @param cub Pointer to the main t_cub3d context structure.
 * @note Relies on `cub->mlx` being valid.
 */
static void	clean_frame(t_cub3d *cub)
{
	if (cub->mlx && cub->frame.img_ptr)
	{
		mlx_destroy_image(cub->mlx, cub->frame.img_ptr);
		cub->frame.img_ptr = NULL;
	}
}

/**
 * @brief Orchestrates the entire program cleanup process.
 * Calls specialized static functions to clean MLX resources in the
 * correct order (images/window first, then MLX connection), followed
 * by freeing the map's memory.
 * This function is called by `cleanup_and_exit` just before
 * program termination.
 * @param cub Pointer to the main t_cub3d context structure.
 * @note The cleanup order is critical: MLX images/windows must be destroyed
 * before destroying the MLX display/handler (`clean_mlx`).
 */
void	cleanup(t_cub3d *cub)
{
	if (!cub)
		return ;
	clean_frame(cub);
	clean_window(cub);
	clean_textures(cub);
	free_map(&cub->map);
	clean_mlx(cub);
}
