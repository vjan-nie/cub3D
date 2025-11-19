/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:51:42 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:21:00 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** get_max_line_length:
** Recorre todas las líneas del mapa y devuelve la longitud
** de la más larga.
**
** ¿Para qué sirve esto?
** Para poder "normalizar" el mapa después, rellenando
** las líneas más cortas con espacios y hacer un mapa rectangular.
*/
int	get_max_line_length(char **grid)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/*
** is_line_empty:
** Devuelve true si la línea está vacía o solo contiene
** espacios / tabs.
**
** Esto es útil para:
** - saltar líneas vacías al parsear configuración
** - detectar si hay huecos sospechosos dentro del mapa
*/
bool	is_line_empty(const char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

/*
** is_texture_line:
** Detecta si una línea de configuración es una textura:
**   NO ./north.xpm
**   SO ./south.xpm
**   WE ./west.xpm
**   EA ./east.xpm
**
** No comprueba el path, solo la "etiqueta".
*/
bool	is_texture_line(const char *line)
{
	if (!line)
		return (false);

	if (!ft_strncmp(line, "NO ", 3))
		return (true);
	if (!ft_strncmp(line, "SO ", 3))
		return (true);
	if (!ft_strncmp(line, "WE ", 3))
		return (true);
	if (!ft_strncmp(line, "EA ", 3))
		return (true);

	return (false);
}

/*
** is_color_line:
** Detecta si la línea describe un color:
**   F 220,100,0
**   C 225,30,0
**
** Igual que con las texturas: solo reconoce la etiqueta.
*/
bool	is_color_line(const char *line)
{
	if (!line)
		return (false);

	if (!ft_strncmp(line, "F ", 2))
		return (true);
	if (!ft_strncmp(line, "C ", 2))
		return (true);

	return (false);
}

