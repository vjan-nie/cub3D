/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:11 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/27 11:27:26 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

	if (!check_extension(path))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);

	joined = ft_strdup("");
	while ((line = get_next_line(fd)))
	{
		char *tmp = joined;
		joined = ft_strjoin(joined, line);  // concatenamos
		free(tmp);
        // importan los frees: gnl aloca cada línea
		free(line);
	}
	close(fd);

	// convertimos el texto completo en array de líneas
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
		return (ft_error("Failed to read .cub file\n"), false);

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
