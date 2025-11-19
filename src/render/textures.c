/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:01:08 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 11:46:46 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Carga una sola textura desde un archivo XPM
// cub: estructura principal del juego
// tex: estructura donde se guardará la textura
// path: ruta del archivo XPM
// Devuelve true si se carga correctamente, false si hay error
static bool	load_one_texture(t_cub3d *cub, t_img *tex, char *path)
{
	// Punteros y tamaños de la imagen
	int	width;
	int	height;

	width = 0;
	height = 0;

	// Cargar la imagen XPM en memoria usando MiniLibX
	tex->img_ptr = mlx_xpm_file_to_image(cub->mlx, path, &width, &height);
	if (!tex->img_ptr)
		return (ft_error("Failed to load XPM texture")); // Error si no se carga

	tex->width = width;
	tex->height = height;

	// Obtener puntero a los datos de la imagen para acceder píxel por píxel
	tex->data = mlx_get_data_addr(tex->img_ptr,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->data)
		return (ft_error("Failed to get texture data")); // Error si falla

	return (true); // Textura cargada correctamente
}

// Verifica que las rutas de las 4 texturas (N, S, E, W) estén presentes en el mapa
// Devuelve true si todas están presentes, false si falta alguna
static bool	check_paths(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!map->tex_paths[i])
			return (ft_error("Missing texture path")); // Faltan rutas
		i++;
	}
	return (true); // Todas las rutas existen
}

// Carga todas las texturas del juego (N, S, E, W)
// Primero verifica que las rutas estén definidas y luego carga cada textura
// Devuelve true si todo se cargó correctamente
bool	load_textures(t_cub3d *cub)
{
	int	i;

	// Verificar rutas antes de cargar
	if (!check_paths(&cub->map))
		return (false);

	// Cargar cada textura
	i = 0;
	while (i < 4)
	{
		if (!load_one_texture(cub, &cub->textures[i], cub->map.tex_paths[i]))
			return (false); // Error si falla alguna textura
		i++;
	}
	return (true); // Todas las texturas cargadas correctamente
}
