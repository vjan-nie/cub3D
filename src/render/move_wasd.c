/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_wasd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:00:28 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:34:59 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Mueve al jugador hacia adelante en la dirección en la que está mirando.
// Utiliza el vector de dirección (dir_x, dir_y) multiplicado por la velocidad
// de movimiento, y delega la comprobación de colisiones a check_and_move.
void	move_forward(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed; // Determina cuánto se mueve el jugador por frame
	check_and_move(cub, p->dir_x * speed, p->dir_y * speed);
}

// Mueve al jugador hacia atrás, en sentido opuesto a donde mira.
// Multiplica la dirección por -1 para invertir el movimiento.
void	move_backward(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, -p->dir_x * speed, -p->dir_y * speed);
}

// Mueve al jugador lateralmente hacia la izquierda (strafe left).
// Se usa el vector perpendicular a la dirección de visión (plane_x, plane_y),
// multiplicado por -1 para ir hacia la izquierda.
void	move_left(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, -p->plane_x * speed, -p->plane_y * speed);
}

// Mueve al jugador lateralmente hacia la derecha (strafe right).
// Se usa el vector perpendicular a la dirección de visión, sin invertir.
void	move_right(t_cub3d *cub)
{
	t_player	*p;
	double		speed;

	p = &cub->player;
	speed = p->move_speed;
	check_and_move(cub, p->plane_x * speed, p->plane_y * speed);
}
