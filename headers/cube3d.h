/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:43:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/29 16:12:31 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <sys/time.h>
# include <bits/types/struct_timeval.h>
# include <linux/limits.h>
# include <X11/X.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define SKY_COLOR 0xFF5EACFF
# define GROUND_COLOR 0xFF170501

# define HEIGHT 540
# define WIDTH 960
# define HEIGHT_WIN 1080
# define WIDTH_WIN 1920

# define TILE_SIZE 64
# define PLAYER_SPEED 0.04
# define PLAYER_SIZE 8
# define ROT_SPEED 0.05
# define MINIMAP_SIZE 5

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

struct s_argb
{
	t_uchar		b;
	t_uchar		g;
	t_uchar		r;
	t_uchar		a;
};

union u_color
{
	t_uchar			tab[4];
	struct s_argb	argb;
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
	float	x;
	float	y;
}	t_posf;

typedef struct s_direction
{
	int		forward;
	int		backward;
	int		right;
	int		left;
    int		rotating;
}	t_direction;

typedef struct s_tile
{
	int		dir;
	t_pos	pos;
}	t_tile;

typedef struct s_sprite_slice
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_sprite_slice;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
	int		pixels;
}	t_data;

typedef struct s_player_data
{
	t_pos		index_pos;
	t_pos		pixel_pos;
	t_posf		float_pos;
	t_direction	movement;
}	t_player_data;

typedef struct s_ray
{
	float	dir_x;
	float	dir_y;
	float	camera_x;
	float	delta_dist_x;
	float	delta_dist_y;
	float	step_x;
	float	step_y;
	float	side_dist_x;
	float	side_dist_y;
	float	pos_x;
	float	pos_y;
	float	plane_x;
	float	plane_y;
	float	ray_dir_x;
	float	ray_dir_y;
	/*raycast floor ceilling*/
	float	ray_dir_x_first;
	float	ray_dir_y_first;
	float	ray_dir_x_sec;
	float	ray_dir_y_sec;
	int		horizon_point;
	float	pos_z;
	float	row_distance;
	float	floor_step_y;
	float	floor_step_x;
	float	floor_x;
	float	floor_y;

	float	wall_x;
	float	dist_wall;
	float	dist_player;
	float	current_dist;
	float	floor_x_wall;
	float	floor_y_wall;
	/*endif lmao*/
	int		hit;
	t_pos	map_pos;
	float	perp_wall_dist;
	int		side;
	t_pos	end_ray;
	t_pos	initial_pos;
}	t_ray;

enum e_layer
{
	LAYER_SCREEN,
	LAYER_OVERLAY,
	LAYER_TILE_MAP,
	LAYER_MINIMAP,
	LAYER_MAP,
	LAYER_RAYCAST,
	LAYER_FLOOR,
	LAYER_MONITOR,
	LAYER_ACHANGER,
	LAYER_ACHANGER2
};

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_data			floor;
	t_data			layer[10];
	t_tile			tile[50];
	int				*stats_tile;
	t_pos			size_map;
	t_posf			offset;
	char			**map;
	t_player_data	player_data;
	struct timeval	time;
	struct s_info	*stats;
	size_t			fps;
	t_ray			ray;
}	t_mlx;

typedef struct s_tab_size
{
	size_t	row;
	size_t	column;
}	t_tab_size;

enum e_dir
{
	NO,
	SO,
	WE,
	EA	
};

typedef struct s_info
{
	int		map_fd;
	char	texture_path[4][PATH_MAX];
	int		ceiling[3];
	int		floor[3];
	int		texture_valid[4];
	/*0 NO + 1 SO + 2 WE + 3 EA*/
	t_data	img_texture[4];
	t_mlx	*display;
	t_pos	player;
	t_pos	old_pos;
    float	old_angle;
	int		map_is_create;
	char	**map;
}	t_info;

typedef struct s_upscale
{
	t_pos			screen_pos;
	t_pos			rc_pos;
	unsigned int	pixel_color[WIDTH];
	int				nb_pixels;
	int				nb_lines;
	int				nb_px_in_lines;
	float			ratio_h;
	int				i;
	int				j;
	char            *dst;
	int				nb_lines_rc;
	float			ratio_w;
}	t_upscale;

t_tab_size		char_tab_len(char **tab);
void			wall(t_data *img, float distance);

// ------------ PLAYER -------------

int				is_player(char c);
void			get_player_pos(char **map, t_mlx *vars);
t_pos			get_player_index(char **map);
void			player_pos_update(t_mlx *vars, char **map);

// ------------ KEYBOARD -------------

int				key_hook( int keycode, t_mlx *vars);
int				key_released(int keycode, t_mlx *vars);

// ------------ MINIMAP -------------

int				init_mini_map(t_mlx *vars);
t_pos			size_map(char **map);
void			draw_map(t_mlx *game);
int				map_gen(t_mlx *vars, char **map_tab);
void			start_tiles_init(t_mlx *g);
void			autotile_generator(char **map, t_mlx *g);

// ------------ RAYCAST -------------

void			init_value_for_cast(t_ray *ray, t_mlx *vars, t_pos *origin);
int				raycast(t_mlx *vars);

// ------------ IMG UTILS -------------

t_data			new_img(t_mlx *vars, unsigned int width, unsigned int height);
t_data			new_file_img(char *path, t_mlx *window);
unsigned int	get_pixel_img(t_data *img, int x, int y);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
void			get_darker_color(float coef, t_color *color);
float			init_pixel_tex_y(t_pos *current, float step);
int				init_pixel_tex_x(t_ray *ray, t_mlx *vars);
int				*fill_dir_v(int *c, char **map, t_pos pos, t_pos fill);
int				*fill_dir_h(int *c, char **map, t_pos pos, t_pos fill);
int				*l_corner_dir(int *c, t_pos pos, t_mlx g, char **map);
int				*face_corner_v(int *c, t_pos pos, t_mlx g, char **map);
int				*face_corner_h(int *c, t_pos pos, t_mlx g, char **map);
int				*x_dir(int *c, t_pos pos, t_mlx g, t_pos map_size);
void			draw_square(t_data *img, t_pos origin, int size, int color);
// void			my_mlx_pixel_put(const t_data *data, const int x, const int y, const int color);
void			upscale_rc_to_screen(t_mlx *vars, t_data *screen);
// ------------ UTILS -------------

int				print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top);
int				print_floor(t_pos *current, t_mlx *vars, t_ray *ray);
int				print_wall(t_pos *current, t_mlx *vars, float step, \
				t_pos *end, t_data *img);

t_data			select_texture(t_data img[4], t_mlx *vars);
int				vertical_raycast(t_mlx *vars, t_pos *end);
void			fps(const t_mlx *vars);
void			nfree(void *pointer);
void			print_ray_param(t_ray *ray);
void			print_map(char *map[]);


#endif
