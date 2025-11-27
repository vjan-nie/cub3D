/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:40:43 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 02:34:31 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief General utility functions for error handling, MLX setup, and
 * program cleanup.
 * This file contains crucial core functions that manage the program's lifecycle
 * and provide a unified method for error reporting.
 */
#include "cub3d.h"

/**
 * @brief Prints a standardized error message to standard error (fd 2).
 * This function prefixes the message with "Error\n" and is designed to be used
 * in conjunction with the comma operator for conditional return statements.
 * @param msg The specific error string to print (e.g., "Map is not closed").
 */
void	ft_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
}

/**
 * @brief MLX callback function to handle window closing events.
 * This function is registered as a hook for the event 17
 * (window close button/ESC key detected).
 * It delegates the termination process to the main cleanup routine.
 * @param cub Pointer to the main t_cub3d context structure.
 * @return int Always returns 0 (required by the mlx_hook signature).
 */
int	close_window(t_cub3d *cub)
{
	cleanup_and_exit(cub, 0);
	return (0);
}

/**
 * @brief Performs comprehensive resource cleanup and terminates the program.
 * This function serves as a **wrapper** that ensures all allocated resources
 * are freed by calling the `cleanup()` helper function, and then forcibly
 * terminates the program with the specified exit code.
 * @param cub Pointer to the main t_cub3d context structure.
 * @param code The exit code to pass to the system.
 */
void	cleanup_and_exit(t_cub3d *cub, int code)
{
	cleanup(cub);
	exit(code);
}

/**
 * @brief Initializes the MiniLibX window and the primary rendering framebuffer.
 * Sets the window dimensions, creates the MLX window instance, and prepares
 * the initial image buffer where all rendering will take place.
 * @param cub Pointer to the main t_cub3d context structure.
 * @return bool True if the window and framebuffer are created successfully,
 * false otherwise.
 * @details
 * - Uses predefined dimensions (1280x720).
 * - Creates the window via `mlx_new_window`.
 * - Calls `create_frame` to allocate the image buffer (`cub->frame`).
 * @note Failure in `mlx_new_window` triggers `ft_error` and returns false,
 * ensuring safe failure.
 */
bool	init_window(t_cub3d *cub)
{
	cub->screen_width = SCREEN_WIDTH;
	cub->screen_height = SCREEN_HEIGHT;
	cub->win = mlx_new_window(cub->mlx,
			cub->screen_width, cub->screen_height, "cub3D");
	if (!cub->win)
		return (ft_error("Failed to create window\n"), false);
	create_frame(cub, &cub->frame);
	return (true);
}
