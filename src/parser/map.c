/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:11 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/28 13:51:38 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check_map_block:
** Comprueba que no haya líneas vacías dentro del bloque del mapa.
** Considera válidos los espacios dentro del mapa.
*/
static bool	check_map_block(const char *joined, int start)
{
	int		i;
	int		line_start;
	int		j;
	bool	has_tile;

	i = start;
	line_start = start;
	while (joined[i])
	{
		if (joined[i] == '\n' || joined[i + 1] == '\0')
		{
			has_tile = false;
			j = line_start;
			while (j <= i)
			{
				if (joined[j] == '1' || joined[j] == '0' || joined[j] == 'N' || joined[j] == 'S' ||
					joined[j] == 'E' || joined[j] == 'W')
					has_tile = (true);
				j++;
			}
			if (!has_tile)
				return (ft_error("Map contains empty lines inside, stop reading\n"), false);
			line_start = i + 1;
		}
		i++;
	}
	return (true);
}

/*
** find_map_start:
** Devuelve el índice donde aparece el primer carácter de mapa ('1','0','N','S','E','W')
** dentro de una línea no vacía y que no sea de configuración.
*/
static bool	in_map(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' ||
			line[i] == 'N' || line[i] == 'S' ||
			line[i] == 'E' || line[i] == 'W')
			return (true);
		i++;
	}
	return (false);
}

/*
** read_file_lines:
** Lee *todo* el archivo .cub y devuelve un array de líneas.
**
** Cómo funciona:
** - Abre el archivo
** - Va acumulando todo en un string grande usando gnl
** - Luego hace un split por '\n' para obtener cada línea
**
** ¿Por qué así?  
** Porque parsear línea por línea directamente complicaría
** separar la parte de configuración de la parte del mapa.
**
** Nota: Esta función devuelve NULL si el archivo no se puede abrir.
*/
static char	**read_file_lines(const char *path)
{
	int		fd;
	char	*line;
	char	*joined;
	char	**lines;
	char	*tmp;
	int		map_start;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	joined = ft_strdup("");
	map_start = -1;
	while ((line = get_next_line(fd)))
	{
		if (map_start == -1 && !is_texture_line(line)
			&& !is_color_line(line) && !is_line_empty(line))
				if (in_map(line))
					map_start = ft_strlen(joined);
		tmp = joined;
		joined = ft_strjoin(joined, line);
		free(tmp);
		free(line);
	}
	close(fd);
	if (map_start >= 0 && !check_map_block(joined, map_start))
		return (free(joined), NULL);
	lines = ft_split(joined, '\n');
	free(joined);
	return (lines);
}

/*
** load_and_validate_map:
** Función que coordina toda la carga del archivo .cub.
** Aquí se hace el “pipeline” de procesamiento real.
**
** Pasos:
** 1) Leemos todas las líneas del archivo.
** 2) parse_config → detecta texturas, colores, etc.
** 3) parse_map → extrae solo la parte del mapa en sí.
** 4) normalize_map → hace el mapa rectangular (rellena con espacios).
** 5) validate_map → comprueba que el mapa está cerrado y es jugable.
**
** Si algo falla, liberamos file_lines y devolvemos false.
** Si todo va bien, devolvemos true y el t_map está listo para usar.
*/
bool	load_and_validate_map(t_map *map, const char *path)
{
	char	**file_lines;

	file_lines = read_file_lines(path);
	if (!file_lines)
		return (ft_error("Map read error\n"), false);

	if (!parse_config(map, file_lines))
		return (ft_free_array(file_lines), false);

	if (!parse_map(map, file_lines))
		return (ft_free_array(file_lines), false);

	normalize_map(map);

	if (!validate_map(map))
		return (ft_free_array(file_lines), false);

	ft_free_array(file_lines);
	return (true);
}
