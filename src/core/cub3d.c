/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:56:53 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/24 14:15:39 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*  
** main_loop:
** Este es el ciclo que se ejecuta en *cada frame*.
** - Si pulsas ESC, se cierra la ventana.
** - Actualiza al jugador según teclas pulsadas.
** - Renderiza un nuevo frame completo.
** - Manda el frame ya dibujado a la ventana.
** Básicamente: INPUT → UPDATE → DRAW.
*/
static int	main_loop(t_cub3d *cub)
{
	if (cub->key_code.esc)
		close_window(cub);
	update_player(cub);
	render_frame(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->frame.img_ptr, 0, 0);
	return (0);
}

/*
** init_graphics:
** Arranca MLX. Sin esto no existe ventana ni imágenes.
** No crea aún la ventana, solo inicializa el motor gráfico.
** Devuelve false si algo falla para parar limpio.
*/
static int	init_graphics(t_cub3d *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (ft_error("MLX init failed"));
	return (1);
}

/*
** load_game:
** Carga TODO lo que depende del archivo .cub y
** deja el programa ya listo para empezar.
**
** Pasos:
** 1) Carga y valida el mapa y configuraciones.
** 2) Crea la ventana y el frame.
** 3) Carga las texturas NO/SO/EA/WE.
** 4) Calcula dónde está el jugador y su orientación.
**
** Si algo falla, devuelve false para abortar la ejecución.
*/
static int	load_game(t_cub3d *cub, const char *path)
{
	if (!load_and_validate_map(&cub->map, path))
		return (0);
	if (!init_window(cub))
		return (0);
	if (!load_textures(cub))
		return (0);
	init_player(&cub->player, &cub->map);
	return (1);
}

/*
** init_cub3d:
** Deja toda la estructura t_cub3d limpia desde cero,
** inicializa MLX y luego llama a la carga del juego.
**
** Este es el "setUp" general del engine.
*/
static int	init_cub3d(t_cub3d *cub, const char *path)
{
	ft_bzero(cub, sizeof(t_cub3d));
	if (!init_graphics(cub))
		return (0);
	if (!load_game(cub, path))
		return (0);
	return (1);
}

/*
** main:
** Punto de entrada del programa.
**
** - Comprueba argumentos (necesita un mapa)
** - Inicializa todo el engine
** - Configura los hooks para teclado y cierre
** - Enchufa el loop principal de MLX
**
** Después de mlx_loop(), ya todo va por eventos y por main_loop.
*/
int	main(int argc, char **argv)
{
	t_cub3d	cub;

	if (argc != 2)
		return (ft_error("Usage: ./cub3D <map.cub>"), 1);
	ft_bzero(&cub, sizeof(t_cub3d));
	if (!init_cub3d(&cub, argv[1]))
		return (1);
	mlx_hook(cub.win, 2, 1L << 0, on_key_press, &cub); //evento 2: key press, llamamos a on_key_press (1L << 0 funciona como máscara?)
	mlx_hook(cub.win, 3, 1L << 1, on_key_release, &cub); //evento 3: key release
	mlx_hook(cub.win, 17, 0L, close_window, &cub); //evento 17: destoy, notify: salir
	mlx_loop_hook(cub.mlx, main_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
