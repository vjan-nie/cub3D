/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:07:54 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 02:24:20 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file key_handler.c
 * @brief Handles the capture and state tracking of user keyboard input.
 * Implements the MiniLibX hook functions to capture key press and release
 * events, updating the boolean flags in the t_input structure.
 * This state-based approach allows for smooth, continuous movement in the
 * main loop.
 */

#include "cub3d.h"

/**
 * @brief Sets the boolean state (pressed or released) for a specific key code.
 * This function is an internal utility to centralize the logic for toggling
 * the input flags within the t_input structure.
 * @param keys Pointer to the t_input structure (t_cub3d::key_code).
 * @param key The integer key code received from the MLX hook.
 * @param state The desired state: 'true' for key press, 'false' for
 * key release.
 */
static void	set_key_state(t_input *keys, int key, bool state)
{
	if (key == KEY_W)
		keys->w = state;
	else if (key == KEY_A)
		keys->a = state;
	else if (key == KEY_S)
		keys->s = state;
	else if (key == KEY_D)
		keys->d = state;
	else if (key == KEY_LEFT)
		keys->left = state;
	else if (key == KEY_RIGHT)
		keys->right = state;
	else if (key == KEY_ESC)
		keys->esc = state;
}

/**
 * @brief MLX hook function executed when a keyboard key is pressed.
 * This function marks the corresponding key flag in the t_input
 * structure as 'true'.
 * The actual player movement is deferred to the update_player() function in
 * the main loop.
 * @param keycode The integer code of the pressed key.
 * @param cub Pointer to the main t_cub3d context structure.
 * @return int Always returns 0.
 */
int	on_key_press(int keycode, t_cub3d *cub)
{
	set_key_state(&cub->key_code, keycode, true);
	return (0);
}

/**
 * @brief MLX hook function executed when a keyboard key is released.
 * This function marks the corresponding key flag in the t_input
 * structure as 'false', effectively stopping the movement/rotation associated
 * with that key on the next frame update.
 * @param keycode The integer code of the released key.
 * @param cub Pointer to the main t_cub3d context structure.
 * @return int Always returns 0 (required by mlx_hook signature).
 */
int	on_key_release(int keycode, t_cub3d *cub)
{
	set_key_state(&cub->key_code, keycode, false);
	return (0);
}
