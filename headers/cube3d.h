/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:43:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/23 19:22:05 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <sys/time.h>
# include <X11/X.h>
# include <bits/types/struct_timeval.h>
# include <linux/limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

// # define SIZE_IMG 1024
# define SKY_COLOR 0xFF5EACFF
# define GROUND_COLOR 0xFF170501

# define HEIGHT 270
# define WIDTH 480
# define HEIGHT_WIN 1080
# define WIDTH_WIN 1920

# define TILE_SIZE 64
# define PLAYER_SPEED 4
# define PLAYER_SIZE 8

# define MINIMAP_SIZE 5

typedef unsigned char t_uchar;
typedef unsigned int t_uint;

struct s_argb {
    t_uchar b;
    t_uchar g;
    t_uchar r;
    t_uchar a;
};

union u_color {
    t_uchar tab[4];
    struct s_argb    argb;
    struct {
        t_uchar b;
        t_uchar g;
        t_uchar r;
        t_uchar a;
    };
    t_uint x;
};

typedef union u_color t_color;

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
	int		forward;
	int		backward;
	int		right;
	int		left;
    float		rotating;
    int		rotation_speed;
}	t_direction;

typedef struct s_tile
{
	int		dir;
	t_pos	pos;
}				t_tile;

typedef struct s_sprite_slice
{
	int	x;
	int	y;
	int	width;
	int	height;
}			t_sprite_slice;

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

typedef struct s_player_data
{
	t_pos	index_pos;
	t_pos	pixel_pos;
	t_posf	float_pos;

}	t_player_data;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	camera_x;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		hit;
	t_pos	map_pos;
	double	perp_wall_dist;
	int		side;
	t_pos	end_ray;
	t_pos	initial_pos;
}	t_ray;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_data			img;
	t_data			overlay;
	int				distance;
	t_data			map_img;
	t_data			mini_map;
	t_data			tilemap;
	t_data			screen;
	t_tile			tile[50];
	int				*stats_tile;
	t_pos			size_map;
	t_pos			offset;
	char			**map;
	t_direction		movement;
	size_t			fps;
	struct timeval	time;
	t_pos				carac_index;
	t_pos			carac_pos;
	struct s_info	*stats;
	t_ray			ray;
}	t_mlx;

typedef struct s_tab_size
{
	size_t	row;
	size_t	column;
}	t_tab_size;

typedef struct s_info
{
	int		map_fd;
	char	texture_path[4][PATH_MAX];
	int		ceiling[3];
	int		floor[3];
	int		texture_valid[4];
	t_data	img_texture[4];
	t_mlx	*display;
	t_pos	player;
	t_pos	old_pos;
    float	old_angle;
	int		map_is_create;
	char	**map;

}	t_info;

void			nfree(void *pointer);
void			carac_pos_update(t_pos *offset, t_pos *carac_pos, char **map);
int				map_gen(t_mlx *vars, char **map_tab);
void			draw_square(t_data *img, t_pos origin, int size, int color);
void			my_draw_line(t_pos origin, t_pos end, t_data *img);
t_tab_size		char_tab_len(char **tab);
void			print_map(char *map[]);
t_data			new_img(t_mlx *vars, unsigned int width, unsigned int height);
void			carac_pos_update(t_pos *offset, t_pos *carac_pos, char **map);
int				map_gen(t_mlx *vars, char **map_tab);
void			my_draw_line(t_pos origin, t_pos end, t_data *img);
t_tab_size		char_tab_len(char **tab);
void			print_map(char *map[]);
t_data			new_img(t_mlx *vars, unsigned int width, unsigned int height);
unsigned int	get_pixel_img(t_data *img, int x, int y);
void			draw_horizon(t_data *img);
void			draw_line_from_mid(t_data *img, t_pos origin, int distance);
void			wall(t_data *img, float distance);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				create_trgb(int t, int r, int g, int b);
int				raycast_one_vector(char **map);
int				ray_dist(t_mlx *vars);
t_data			resize_img(t_mlx *vars, t_data *img, unsigned int width, \
				unsigned int height);
int				init_mini_map(t_mlx *vars, t_pos carac_pos);
t_pos			size_map(char **map);
void			autotile_generator(char **map, t_mlx *g);
void			start_tiles_init(t_mlx *g);
t_data			new_file_img(char *path, t_mlx *window);
void			draw_map(t_mlx *game);
int				*fill_dir_v(int *c, char **map, t_pos pos, t_pos fill);
int				*fill_dir_h(int *c, char **map, t_pos pos, t_pos fill);
int				*l_corner_dir(int *c, t_pos pos, t_mlx g, char **map);
int				*face_corner_v(int *c, t_pos pos, t_mlx g, char **map);
int				*face_corner_h(int *c, t_pos pos, t_mlx g, char **map);
int				*x_dir(int *c, t_pos pos, t_mlx g, t_pos map_size);
int				is_carac(char c);
int				raycast(t_mlx *vars);
t_pos			get_carac_pos(char **map, t_pos *offset);
t_pos			get_carac_index(char **map);
void			print_ray_param(t_ray *ray);
void			init_value_for_cast(t_ray *ray, t_mlx *vars, t_pos *origin);
int				key_hook( int keycode, t_mlx *vars);
int				key_released(int keycode, t_mlx *vars);
float			init_pixel_tex_y(t_pos *current, double step);
int				init_pixel_tex_x(t_ray *ray, t_mlx *vars);
void			get_darker_color(float coef, t_color *color);
int				print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top);
int				print_floor(t_pos *current, t_mlx *vars, t_ray *ray);
int				print_wall(t_pos *current, t_mlx *vars, double step, \
				t_pos *end);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

#endif
