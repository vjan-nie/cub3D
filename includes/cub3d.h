/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:05 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/19 10:28:45 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include "libft.h"
# include "structs.h"

# define TILE_SIZE 64

// MAIN_UTILS
bool	ft_error(char *msg);
bool	init_window(t_cub3d *cub);
int		close_window(t_cub3d *cub);
int		on_key_press(int keycode, t_cub3d *cub);
int		on_key_release(int keycode, t_cub3d *cub);
void	cleanup_and_exit(t_cub3d *cub);

// MAP
bool	validate_map(t_map *map);
bool	load_and_validate_map(t_map *map, const char *path);
void	free_map(t_map *map);
void	*free_map_return(t_map *map);
void	free_textures(char **paths);
bool	is_line_empty(const char *line);
bool	is_texture_line(const char *line);
bool	is_color_line(const char *line);
int		get_max_line_length(char **grid);
void	normalize_map(t_map *map);
void	ft_free_array(char **array);

// PARSER
bool	parse_map(t_map *map, char **lines);
bool	parse_config(t_map *map, char **lines);
bool	parse_texture(t_map *map, const char *line);
bool	parse_color(t_map *map, const char *line);
int		parse_rgb(const char *str);

// PLAYER
void	init_player(t_player *p, t_map *map);
bool	is_player_direction(char c);
char	find_player_tile(t_map *map, int *px, int *py);
void	update_player(t_cub3d *cub);

// RENDER
void	render_frame(t_cub3d *cub);
void	create_frame(t_cub3d *cub, t_img *img);
void	put_pixel(t_img *img, int x, int y, int color);

// RAYCAST
void	raycast(t_cub3d *cub);
void	calc_line_params(t_cub3d *cub, t_ray *r);
void	calc_step_side(t_player *p, t_ray *r);
void	calc_delta(t_ray *r);

// TEXTURES
bool	load_textures(t_cub3d *cub);

// MOVEMENT
void	check_and_move(t_cub3d *cub, double mx, double my);
void	move_forward(t_cub3d *cub);
void	move_backward(t_cub3d *cub);
void	move_left(t_cub3d *cub);
void	move_right(t_cub3d *cub);
void	rotate_right(t_cub3d *cub);
void	rotate_left(t_cub3d *cub);

#endif
