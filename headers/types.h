/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/08 16:48:32 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define SKY_COLOR 0xFF5EACFF
# define GROUND_COLOR 0xFF170501

# include <stddef.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <linux/limits.h>

# ifdef BONUS
#  include <sys/time.h>
#  include <bits/types/struct_timeval.h>
# endif
# define TILE_SIZE 64
# define PLAYER_SPEED 0.08
# define PLAYER_SIZE 8
# define ROT_SPEED 0.08
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
	struct
	{
		t_uchar	b;
		t_uchar	g;
		t_uchar	r;
		t_uchar	a;
	};
	t_uint			x;
};

typedef union u_color	t_color;

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
	int		bits_per_line;
}	t_data;

typedef struct s_player_data
{
	t_pos		index_pos;
	t_pos		pixel_pos;
	t_posf		float_pos;
	t_direction	movement;
	int			is_moving;
}	t_player_data;

typedef struct s_ray
{
	t_posf	dir;
	float	camera_x;
	t_posf	delta_dist;
	t_posf	w_step;
	t_posf	side_dist;
	t_posf	pos;
	t_posf	plane;
	t_posf	ray_dir;
	/*raycast floor ceilling*/
	float	row_distance;
	t_posf	f_step;
	t_posf	floor;

	float	wall_x;
	float	dist_wall;
	float	dist_player;
	float	current_dist;
	t_posf	floor_wall;
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
	LAYER_ACHANGER
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
	t_data			animation[4];
	struct timeval	time;
	struct s_info	*stats;
	size_t			fps;
	t_ray			ray;
	unsigned int	light;
	int				mouse;
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
	t_posf	old_pos;
	float	old_angle;
	int		map_is_create;
	char	**map;
}	t_info;

enum
{
	NORTH = -1,
	EAST,
	SOUTH,
	WEST,
};

#endif //TYPES_H
