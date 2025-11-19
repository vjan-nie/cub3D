/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:23 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 12:07:19 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calcula las distancias relativas del rayo a la siguiente línea de celda en X e Y
// delta_x y delta_y representan "cuánto tengo que avanzar en el rayo para cruzar una celda"
// Se usa fabs(1 / dir) porque la distancia depende de la inclinación del rayo
void	calc_delta(t_ray *r)
{
	if (r->dir_x == 0)
		r->delta_x = 1e30; // Evita división por cero, valor muy grande
	else
		r->delta_x = fabs(1.0 / r->dir_x);

	if (r->dir_y == 0)
		r->delta_y = 1e30; // Evita división por cero
	else
		r->delta_y = fabs(1.0 / r->dir_y);
}

// Calcula el paso y la distancia inicial a la siguiente línea de celda
// step_x/step_y = dirección en la cuadrícula (+1 o -1)
// side_x/side_y = distancia que falta para llegar al próximo borde de celda
void	calc_step_side(t_player *p, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (p->x - r->map_x);
		if (r->side_x < 1e-6) 
			r->side_x = 1e-6;      // evita cero
		r->side_x *= r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - p->x);
		if (r->side_x < 1e-6)
			r->side_x = 1e-6;
		r->side_x *= r->delta_x;
	}

	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (p->y - r->map_y);
		if (r->side_y < 1e-6)
			r->side_y = 1e-6;
		r->side_y *= r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - p->y);
		if (r->side_y < 1e-6)
			r->side_y = 1e-6;
		r->side_y *= r->delta_y;
	}
}

// Calcula la altura de la línea a dibujar y el color según la orientación del muro
// También calcula la distancia perpendicular para corregir el efecto de "fish-eye"
// Calcula altura de pared y rangos de dibujo vertical seguro
void	calc_line_params(t_cub3d *cub, t_ray *r)
{
	if (r->side == 0)
		r->perp = (r->map_x - cub->player.x + (1 - r->step_x) / 2) / r->dir_x;
	else
		r->perp = (r->map_y - cub->player.y + (1 - r->step_y) / 2) / r->dir_y;

	if (r->perp <= 0.0)
		r->perp = 0.0001;

	r->line_h = (int)(cub->screen_height / r->perp);
	if (r->line_h > cub->screen_height * 10) // limita alturas extremas
		r->line_h = cub->screen_height * 10;

	r->start = -r->line_h / 2 + cub->screen_height / 2;
	if (r->start < 0)
		r->start = 0;

	r->end = r->line_h / 2 + cub->screen_height / 2;
	if (r->end >= cub->screen_height)
		r->end = cub->screen_height - 1;
}



/* calc_delta

Define cuánto debe avanzar el rayo para cruzar una celda en X o Y.

Es la base del DDA, permite calcular qué lado del muro se toca primero.

calc_step_side

Determina la dirección de paso (izquierda/derecha, arriba/abajo) y la distancia inicial al primer borde.

Con estas variables, perform_dda sabe cuándo moverse en X o Y.

calc_line_params

Corrige la perspectiva usando distancia perpendicular (perp) para evitar que las paredes cercanas se vean distorsionadas.

Calcula la altura de la línea (line_h) y el color según el lado del muro, dando sensación de profundidad.

calc_line_bounds

Asegura que las líneas verticales no salgan de los límites de la pantalla. */