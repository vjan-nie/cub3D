/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:31:48 by vjan-nie          #+#    #+#             */
/*   Updated: 2025/11/18 17:27:33 by vjan-nie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    char    *tex_paths[4];
    int     floor_color;
    int     ceiling_color;
}   t_map;

typedef struct s_player
{
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    double  move_speed;
    double  rot_speed;
}   t_player;

typedef struct s_img
{
    void    *img_ptr;
    char    *data;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_input
{
    bool    w;
    bool    a;
    bool    s;
    bool    d;
    bool    left;
    bool    right;
    bool    esc;
}   t_input;

typedef struct s_cub3d
{
    void        *mlx;
    void        *win;
    t_map       map;
    t_player    player;
    t_img       frame;
    t_img       textures[4];
    int         screen_width;
    int         screen_height;
    t_input     key_code;
}   t_cub3d;

typedef enum e_keycode
{
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_ESC = 65307
}	t_keycode;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	perp;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	int		line_h;
	int		start;
	int		end;
	int		color;
}	t_ray;

#endif
