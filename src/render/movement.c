/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:47:14 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:33:25 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** is_walkable:
** Determina si una celda del mapa puede ser ocupada por el jugador.
** Retorna true si:
** - '0': suelo libre
** - 'N', 'S', 'E', 'W': posición inicial del jugador
** Esto evita que el jugador atraviese paredes ('1') o espacios vacíos (' ').
*/
static bool	is_walkable(char c)
{
	if (c == '0')
		return (true);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

/*
** check_and_move:
** Mueve al jugador según un delta (mx, my) que representa el
** desplazamiento en el eje X e Y respectivamente.
**
** Lógica:
** - Calcula la próxima posición en x e y.
** - Solo actualiza la coordenada si la celda siguiente es caminable.
**
** Esto permite:
** - Mover en horizontal y vertical sin atravesar paredes.
** - Mantener colisiones simples con el mapa.
*/
void	check_and_move(t_cub3d *cub, double mx, double my)
{
	t_player	*p;
	int			next_x;
	int			next_y;

	p = &cub->player;

	// Calcula la posición que tendría el jugador después del movimiento
	next_x = (int)(p->x + mx);
	next_y = (int)(p->y + my);

	// Movimiento horizontal
	if (is_walkable(cub->map.grid[(int)p->y][next_x]))
		p->x += mx;

	// Movimiento vertical
	if (is_walkable(cub->map.grid[next_y][(int)p->x]))
		p->y += my;
}

/* Explicación paso a paso:

mx y my:

Son pequeños incrementos que provienen del teclado o de la rotación.

Por ejemplo, si presionas W, mx y my se calculan usando la dirección del jugador y la velocidad de movimiento.

Casting a int:

Convierte la posición flotante del jugador a coordenadas del mapa (int) para verificar la celda correspondiente.

Esto asegura que revisamos la celda correcta en la cuadrícula.

Chequeo de colisión independiente:

Primero horizontal, luego vertical. Esto evita que el jugador atraviese esquinas entre paredes.

Restricción del movimiento:

Solo se puede avanzar a celdas que sean caminables (0, N, S, E, W). */
