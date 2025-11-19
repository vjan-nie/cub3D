/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:01:22 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 11:31:28 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función interna que rota tanto el vector de dirección como el vector del plano de visión
// del jugador. Esto permite que la cámara gire sin cambiar la posición del jugador.
// - `rot` es el ángulo de rotación en radianes (positivo = izquierda, negativo = derecha).
static void	rotate_dir_plane(t_player *p, double rot)
{
	rot = -rot;
	double	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	double old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

// Gira al jugador hacia la izquierda.
// La rotación es positiva, usando la velocidad de rotación definida en player.
void	rotate_left(t_cub3d *cub)
{
	t_player	*p;
	double		rot;

	p = &cub->player;
	rot = p->rot_speed; // Ángulo de rotación por frame
	rotate_dir_plane(p, rot);
}

// Gira al jugador hacia la derecha.
// La rotación es negativa, lo que invierte la dirección de giro.
void	rotate_right(t_cub3d *cub)
{
	t_player	*p;
	double		rot;

	p = &cub->player;
	rot = -p->rot_speed; // Rotación invertida
	rotate_dir_plane(p, rot);
}
