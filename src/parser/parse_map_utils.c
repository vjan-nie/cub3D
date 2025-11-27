/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:55:46 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 09:17:01 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** parse_rgb:
** Convierte una string tipo "R,G,B" a un entero 0xRRGGBB.
**
** Pasos:
** 1) Separa la cadena por comas.
** 2) Convierte cada parte a entero (r, g, b).
** 3) Comprueba que estén entre 0 y 255.
** 4) Combina en un solo entero: (r << 16) | (g << 8) | b
**
** Devuelve -1 si hay error en el formato o valores fuera de rango.
*/
int	parse_rgb(const char *str)
{
	char	**p;
	int		r;
	int		g;
	int		b;

	p = ft_split(str, ',');
	if (!p || !p[0] || !p[1] || !p[2])
		return (-1);
	r = ft_atoi(p[0]);
	g = ft_atoi(p[1]);
	b = ft_atoi(p[2]);
	ft_free_array(p);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/*
** parse_color:
** Lee una línea de color tipo "F 220,100,0" o "C 255,255,255"
** y la guarda en map->floor_color o map->ceiling_color.
**
** Devuelve false si:
** - la línea no tiene dos partes
** - el RGB es inválido
** - el tipo no es F o C
*/
bool	parse_color(t_map *map, const char *line)
{
	char	**split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_error("Invalid color line\n"), false);

	int color = parse_rgb(split[1]);
	if (color == -1)
		return (ft_error("Invalid RGB values\n"), false);

	if (!ft_strncmp(split[0], "F", 2))
		map->floor_color = color;
	else if (!ft_strncmp(split[0], "C", 2))
		map->ceiling_color = color;
	else
		return (ft_error("Unknown color type\n"), false);

	ft_free_array(split);
	return (true);
}

/*
** parse_texture:
** Lee una línea tipo "NO ./path_to_texture" y la guarda
** en map->tex_paths en el índice correcto:
** 0=NO, 1=SO, 2=WE, 3=EA
**
** Devuelve false si:
** - la línea no tiene dos partes
** - la dirección NO/SO/WE/EA es desconocida
*/
bool	parse_texture(t_map *map, const char *line)
{
	char	**split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_error("Invalid texture line\n"), false);

	int index = -1;
	if (!ft_strncmp(split[0], "NO", 3)) index = 0;
	else if (!ft_strncmp(split[0], "SO", 3)) index = 1;
	else if (!ft_strncmp(split[0], "WE", 3)) index = 2;
	else if (!ft_strncmp(split[0], "EA", 3)) index = 3;

	if (index == -1)
		return (ft_error("Unknown texture direction\n"), false);

	map->tex_paths[index] = ft_strdup(split[1]);
	ft_free_array(split);
	return (true);
}

/*
** parse_config:
** Recorre las líneas del archivo .cub y carga:
** - 4 texturas (NO, SO, WE, EA)
** - 2 colores (F, C)
**
** Ignora líneas vacías. Si encuentra algo raro, falla.
**
** Devuelve true si exactamente las 6 configuraciones se pudieron parsear.
*/
bool	parse_config(t_map *map, char **lines)
{
	int i = 0;
	int configs_parsed = 0;

	while (lines[i] && configs_parsed < 6)
	{
		if (is_texture_line(lines[i]))
		{
			if (!parse_texture(map, lines[i]))
				return (false);
			configs_parsed++;
		}
		else if (is_color_line(lines[i]))
		{
			if (!parse_color(map, lines[i]))
				return (false);
			configs_parsed++;
		}
		else if (!is_line_empty(lines[i]))
			return (ft_error("Invalid config line\n"), false);
		i++;
	}
	return (configs_parsed == 6);
}
