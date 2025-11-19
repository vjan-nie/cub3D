/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:40:43 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:17:43 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*  
** ft_error:
** Función comodín para imprimir un mensaje de error
** y devolver false.  
** La idea es usarla dentro de condiciones tipo:
**     if (!algo) return ft_error("mensaje");
** para hacer el código más limpio.
*/
bool	ft_error(char *msg)
{
	ft_printf("%s\n", (char *)msg);
	return (false);
}

/*
** close_window:
** Callback que llama MLX cuando se cierra la ventana
** (o cuando tú detectas ESC y quieres cerrar).  
** Solo delega en cleanup_and_exit.
*/
int	close_window(t_cub3d *cub)
{
	cleanup_and_exit(cub);
	return (0);
}

/*
** cleanup_and_exit:
** Limpieza general del programa antes de salir.
** - Borra el frame si existe.
** - Borra la ventana.
** - Borra todas las texturas cargadas.
** - Libera la memoria del mapa.
** - Termina el programa con exit().
**
** OJO: No destruye mlx_init() (MLX no lo requiere en Linux).
** Cuando esto se ejecuta, el programa muere sí o sí.
*/
void	cleanup_and_exit(t_cub3d *cub)
{
	int	i;

	if (cub->frame.img_ptr)
		mlx_destroy_image(cub->mlx, cub->frame.img_ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].img_ptr)
			mlx_destroy_image(cub->mlx, cub->textures[i].img_ptr);
		i++;
	}
	free_map(&cub->map);
	exit(EXIT_SUCCESS);
}

/*
** init_window:
** Configura el tamaño de la ventana, la crea, y luego
** prepara el frame (la imagen donde dibujas cada frame
** antes de pasarlo a la ventana).
**
** Si falla la creación de la ventana, devuelve false.
** Si todo va bien, ya puedes empezar a renderizar.
*/
bool	init_window(t_cub3d *cub)
{
	cub->screen_width = 1024;
	cub->screen_height = 768;
	cub->win = mlx_new_window(cub->mlx,
			cub->screen_width, cub->screen_height, "cub3D");
	if (!cub->win)
		return (ft_error("Failed to create window"));
	create_frame(cub, &cub->frame);
	return (true);
}

