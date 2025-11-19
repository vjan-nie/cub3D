/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:03:18 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:28:30 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** free_textures:
** Libera las rutas de texturas NO/SO/EA/WE almacenadas
** en map->tex_paths.
**
** Solo libera los strings, no imágenes MLX (eso lo hace cleanup).
**
** paths debe tener longitud 4 sí o sí.
*/
void	free_textures(char **paths)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (paths[i])
			free(paths[i]);
		i++;
	}
}

/*
** free_map:
** Libera TODA la memoria asociada al mapa:
** - El grid (mapa en sí)
** - Las rutas de texturas
**
** No toca floor_color ni ceiling_color porque son ints.
** No toca imágenes MLX de texturas, eso es trabajo de cleanup_and_exit.
*/
void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
	{
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	i = 0;
	while (i < 4)
	{
		if (map->tex_paths[i])
			free(map->tex_paths[i]);
		i++;
	}
}

/*
** free_map_return:
** Pequeña función de utilidad para poder hacer cosas como:
**     return free_map_return(map);
**
** Básicamente libera el mapa y devuelve NULL.
** Te permite escribir estructuras más limpias en el parser.
*/
void	*free_map_return(t_map *map)
{
	free_map(map);
	return (NULL);
}

/*
** ft_free_array:
** Sirve para cualquier array
** de strings terminado en NULL.
**
** Es útil para liberar lo que sale de ft_split o funciones similares.
*/
void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
