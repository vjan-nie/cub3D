/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:53 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 02:24:51 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cub3d.c
 * @brief Main entry point, game initialization, and the primary rendering loop.
 * This file contains the main function to start the game, initialize the
 * MiniLibX environment, load the map and textures, and implement the core game
 * loop (main_loop).
 * It orchestrates the setup and continuous execution of the cub3D Raycasting
 * engine.
 */
#include "cub3d.h"

/**
 * @brief The core game loop function, executed on every frame refresh.
 * This function handles the game cycle: input processing, state update,
 * and rendering. Sequence: INPUT -> UPDATE -> DRAW.
 * @param cub Pointer to the main t_cub3d context structure.
 * @return int Always returns 0, unless the ESC key is pressed, in which case
 * it returns the value from close_window.
 * @details
 * 1. Checks if the ESC key state is active to trigger the window closing
 * routine.
 * 2. Updates the player's position and orientation based on accumulated inputs.
 * 3. Renders the new frame using the raycasting algorithm.
 * 4. Pushes the rendered image buffer to the window display.
 */
static int	main_loop(t_cub3d *cub)
{
	if (cub->key_code.esc)
		return (close_window(cub));
	update_player(cub);
	render_frame(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->frame.img_ptr, 0, 0);
	return (0);
}

/**
 * @brief Initializes the MiniLibX graphical engine connection.
 * Starts the MLX library connection. This must be called before creating
 * any windows or images.
 * @param cub Pointer to the main t_cub3d context structure.
 * @return int 1 on successful initialization, 0 on failure.
 * @note If mlx_init() fails, it prints an error message via ft_error
 * and returns 0.
 */
static int	init_graphics(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_error("MLX init failed\n"), 0);
	return (1);
}

/**
 * @brief Loads all game assets and configurations from the map file.
 * This is the high-level setup sequence executed once at the start of the game.
 * @param cub Pointer to the main t_cub3d context structure.
 * @param path The path to the .cub map file.
 * @return bool True on success, false if any loading step fails.
 * @details The steps include:
 * 1) Load and validate map/config.
 * 2) Initialize window/framebuffer.
 * 3) Load textures.
 * 4) Initialize player.
 */
static bool	load_game(t_cub3d *cub, const char *path)
{
	if (!load_and_validate_map(&cub->map, path))
		return (false);
	if (!init_window(cub))
		return (false);
	if (!load_textures(cub))
		return (false);
	init_player(&cub->player, &cub->map);
	return (true);
}

/**
 * @brief Initializes the main game structure and starts the asset
 * loading process.
 * This function serves as the central setup routine before entering the
 * main loop.
 * @param cub Pointer to the t_cub3d structure to be initialized.
 * @param path The path to the .cub map file.
 * @return bool True on success, false on failure.
 * @note Uses ft_bzero to zero-initialize the structure, which is vital
 * for safe cleanup.
 */
static bool	init_cub3d(t_cub3d *cub, const char *path)
{
	ft_bzero(cub, sizeof(t_cub3d));
	if (!init_graphics(cub))
		return (false);
	if (!load_game(cub, path))
		return (false);
	return (true);
}

/**
 * @brief Program entry point for the cub3D raycasting engine.
 * Handles argument validation, initializes the entire game context, sets up
 * event hooks, and starts the MiniLibX event loop.
 * @param argc The number of command-line arguments. Must be 2
 * (program name + map file).
 * @param argv The array of command-line argument strings.
 * @return int 0 on clean exit, 1 on error.
 */
int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
		return (ft_error("Usage: ./cub3D <map.cub>\n"), 1);
	if (!init_cub3d(&cub, argv[1]))
		return (cleanup(&cub), 1);
	mlx_hook(cub.win, 2, 1L << 0, on_key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, on_key_release, &cub);
	mlx_hook(cub.win, 17, 0L, close_window, &cub);
	mlx_loop_hook(cub.mlx, main_loop, &cub);
	mlx_loop(cub.mlx);
	cleanup(&cub);
	return (0);
}
