/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:43:45 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 11:37:00 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Dibuja una línea horizontal completa de un color específico en la imagen
// img: la estructura de la imagen donde se dibuja
// y: fila en la que se dibuja
// color: color de los píxeles
static void	fill_line(t_img *img, int y, int color)
{
	int	x;

	x = 0;
	while (x < img->width)
	{
		put_pixel(img, x, y, color); // Coloca píxel a píxel
		x++;
	}
}

// Dibuja el fondo de la escena: techo y suelo
// La pantalla se divide en dos mitades: arriba = techo, abajo = suelo
static void	draw_background(t_cub3d *cub)
{
	int	y;
	int	half;

	y = 0;
	half = cub->screen_height / 2; // Punto medio de la pantalla

	// Dibujar techo
	while (y < half)
	{
		fill_line(&cub->frame, y, cub->map.ceiling_color);
		y++;
	}

	// Dibujar suelo
	while (y < cub->screen_height)
	{
		fill_line(&cub->frame, y, cub->map.floor_color);
		y++;
	}
}

// Función principal de renderizado
// Primero dibuja el fondo (techo y suelo) y luego los muros usando raycasting
void	render_frame(t_cub3d *cub)
{
	draw_background(cub);
	raycast(cub); // Dibuja muros sobre el fondo
}

// Dibuja un píxel en la imagen
// img: imagen donde dibujar
// x, y: coordenadas del píxel
// color: color del píxel en formato 0xRRGGBB
void	put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;

	dst = img->data + (y * img->line_len + x * (img->bpp / 8));

	dst[0] = color & 0xFF;          // Blue
	dst[1] = (color >> 8) & 0xFF;   // Green
	dst[2] = (color >> 16) & 0xFF;  // Red
	if (img->bpp == 32)
		dst[3] = (color >> 24) & 0xFF; // Alpha si existe
}

// Inicializa la estructura de la imagen y reserva memoria usando MiniLibX
// Se crea un "framebuffer" donde se dibujará cada frame
void	create_frame(t_cub3d *cub, t_img *img)
{
	img->width = cub->screen_width;
	img->height = cub->screen_height;
	img->img_ptr = mlx_new_image(cub->mlx, img->width, img->height); // Crear imagen
	if (!img->img_ptr)
		return ;

	// Obtener puntero a los datos de la imagen para dibujar píxeles manualmente
	img->data = mlx_get_data_addr(
		img->img_ptr, &img->bpp, &img->line_len, &img->endian);
}

/* fill_line / draw_background

Genera el fondo antes de dibujar los muros.

Optimiza dibujando líneas completas en lugar de píxel por píxel.

put_pixel

Función fundamental que escribe directamente en la memoria de la imagen.

Maneja bordes de pantalla para evitar errores de acceso.

create_frame

Prepara un framebuffer donde se dibujará todo el contenido.

mlx_get_data_addr devuelve un puntero a los píxeles que permite manipulación directa.

render_frame

Flujo completo del renderizado por frame: fondo → raycasting (muros).

Cada frame se dibuja sobre el framebuffer antes de ser mostrado en pantalla. */