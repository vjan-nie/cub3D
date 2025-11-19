/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:07:54 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:18:36 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** set_key_state:
** Función interna que simplemente enciende o apaga
** el flag asociado a una tecla concreta.
**
** La idea es que on_key_press y on_key_release no
** tengan lógica repetitiva, solo deleguen aquí.
**
** Cada flag en t_input representa si la tecla está
** pulsada *en este momento*, para que el juego pueda
** mover al jugador de forma continua en cada frame.
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

/*
** on_key_press:
** Se llama cada vez que MLX detecta que una tecla
** ha sido pulsada.
**
** Solo marca el flag correspondiente como "true".
** El movimiento real se hace en update_player().
*/
int	on_key_press(int keycode, t_cub3d *cub)
{
	set_key_state(&cub->key_code, keycode, true);
	return (0);
}

/*
** on_key_release:
** Igual que on_key_press, pero marcando la tecla
** como "false" al soltarse.
**
** Esto permite que puedas moverte manteniendo una
** tecla pulsada, y parar justo cuando la sueltas.
*/
int	on_key_release(int keycode, t_cub3d *cub)
{
	set_key_state(&cub->key_code, keycode, false);
	return (0);
}
