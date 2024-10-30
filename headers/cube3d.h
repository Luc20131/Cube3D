/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:43:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/10/30 16:11:02 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <X11/X.h>
#include <bits/types/struct_timeval.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"

#define SIZE_IMG 1024
#define SKY_COLOR 0xFF5EACFF
#define GROUND_COLOR 0xFF5E3B10
#define FOV 60
#define HEIGHT 1024
#define WIDTH 1024
#define TILE_SIZE 64
#define PLAYER_SPEED 4
#define PLAYER_SIZE 8
#define MINIMAP_SIZE 5

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_posf
{
	double	x;
	double	y;
}	t_posf;

typedef struct s_direction
{
	int	up;
	int	down;
	int	right;
	int	left;
} t_direction;

typedef struct s_vector
{
	t_posf		origin;
	int			direction;
	float		length;
	double		delta_x;
	double		delta_y;
	double		angle;
}	t_vector;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
}	t_data;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_data		img;
	int			distance;
	t_data		map_img;
	t_data		mini_map;
	t_pos		offset;
	char		**map;
	t_direction	movement;
	size_t		fps;
	struct timeval time;
}	t_mlx;

typedef struct s_tab_size
{
	size_t	row;
	size_t	column;
}	t_tab_size;


void	carac_pos_update(t_pos *offset, t_pos *carac_pos, char **map);
int		map_gen(t_mlx *vars, char **map_tab);
void	draw_square(t_data *img, t_pos origin, int size, int color);
void	my_draw_line(t_pos origin, t_pos end, t_data *img);
t_tab_size	char_tab_len(char **tab);
void		print_map(char *map[]);
t_data	new_img(t_mlx *vars, unsigned int width, unsigned int height);
unsigned int	get_pixel_img(t_data *img, int x, int y);
void	draw_horizon(t_data *img);
void	draw_line_from_mid(t_data *img, t_pos origin, int distance);
void	wall(t_data *img, float distance);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	create_trgb(int t, int r, int g, int b);
int	raycast_one_vector(char **map);
int	ray_dist(t_mlx *vars);
t_data	resize_img(t_mlx *vars, t_data *img, unsigned int width, unsigned int height);
int	init_mini_map(t_mlx *vars,t_pos	carac_pos);

#endif
