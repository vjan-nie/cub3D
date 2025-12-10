/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:29:05 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/12/10 14:05:37 by sergio-jime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cub3d.h
 * @brief Main header file containing all necessary includes, constant
 * definitions, and function prototypes for the cub3D project.
 * This header serves as the central interface, aggregating core utilities,
 * parser functions, player logic, rendering routines, and memory
 * management functions.
 */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include <math.h>
# include "libft.h"
# include "structs.h"
# include <mlx.h>

/* ************************************************************************** */
/* Config */

# define TILE_SIZE 64
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define MOVEMENT_SPEED 0.025
# define ROTATION_SPEED 0.025
# define FOV_ANGLE 0.66
# define WALL_MARGIN 0.125

/* ************************************************************************** */
/* Main Utils */

void	ft_error(char *msg);
bool	init_window(t_cub3d *cub);
int		close_window(t_cub3d *cub);
int		on_key_press(int keycode, t_cub3d *cub);
int		on_key_release(int keycode, t_cub3d *cub);
void	cleanup_and_exit(t_cub3d *cub, int code);
void	cleanup(t_cub3d *cub);

/* ************************************************************************** */
/* Map */

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
bool	check_extension(const char *path);

/* ************************************************************************** */
/* Parser */

bool	parse_map(t_map *map, char **lines);
bool	parse_config(t_map *map, char **lines);
int		free_partial_grid(t_map *map, int filled);
int		skip_config(char **lines);
bool	is_valid_char(char c);
bool	in_map(const char *line);
int		parse_rgb(const char *str);

/* ************************************************************************** */
/* Player */

void	init_player(t_player *p, t_map *map);
bool	is_player_direction(char c);
char	find_player_tile(t_map *map, int *px, int *py);
void	update_player(t_cub3d *cub);

/* ************************************************************************** */
/* Render */

void	render_frame(t_cub3d *cub);
void	create_frame(t_cub3d *cub, t_img *img);
void	put_pixel(t_img *img, int x, int y, int color);

/* ************************************************************************** */
/* Raycast */

void	raycast(t_cub3d *cub);
void	calc_line_params(t_cub3d *cub, t_ray *r);
void	calc_step_side(t_player *p, t_ray *r);
void	calc_delta(t_ray *r);
int		clamp(int value, int min, int max);

/* ************************************************************************** */
/* Textures */

bool	load_textures(t_cub3d *cub);
t_img	*select_wall_texture(t_cub3d *cub, t_ray *r);
int		calc_wall_tex_x(t_cub3d *cub, t_ray *r, t_img *tex);

/* ************************************************************************** */
/* Movement */

void	check_and_move(t_cub3d *cub, double mx, double my);
void	move_forward(t_cub3d *cub);
void	move_backward(t_cub3d *cub);
void	move_left(t_cub3d *cub);
void	move_right(t_cub3d *cub);
void	rotate_right(t_cub3d *cub);
void	rotate_left(t_cub3d *cub);

#endif