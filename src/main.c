/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:52:12 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/23 19:50:24 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <stdio.h>

#include "cube3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "parsing.h"
#include "../minilibx-linux/mlx_int.h"
#include "../minilibx-linux/mlx.h"
#define FPS_LIMIT 1200

void	map(t_mlx *vars);
t_pos	get_carac_index(char **map);
t_pos	get_carac_pos(char **map, t_pos *offset);
int		check_colision(t_pos index, t_mlx *vars, char direction);

int	is_carac(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	tick(t_mlx *vars)
{
	vars->carac_index = get_carac_index(vars->map);
	vars->carac_pos = get_carac_pos(vars->map, &vars->offset);
	if (vars->movement.forward)
	{
    	vars->offset.x += (float)(PLAYER_SPEED * vars->ray.dir_x);
    	vars->offset.y += (float)(PLAYER_SPEED * vars->ray.dir_y);
	}
	else if (vars->movement.backward)
	{
    	vars->offset.x -= (float)(PLAYER_SPEED * vars->ray.dir_x);
    	vars->offset.y -= (float)(PLAYER_SPEED * vars->ray.dir_y);
	}
	else if (vars->movement.right)
	{
    	vars->offset.x -= (float)(PLAYER_SPEED * vars->ray.dir_y);
    	vars->offset.y += (float)(PLAYER_SPEED * vars->ray.dir_x);
	}
	else if (vars->movement.left)
	{
    	vars->offset.x += (float)(PLAYER_SPEED * vars->ray.dir_y);
    	vars->offset.y -= (float)(PLAYER_SPEED * vars->ray.dir_x);
	}
	map(vars);
	// usleep(1000000/FPS_LIMIT);
	return (1);
}

t_pos	get_carac_index(char **map)
{
	t_pos	index;

	index.x = 0;
	index.y = 0;
	while (map[index.y])
	{
		index.x = 0;
		while (map[index.y][index.x])
		{
			if (is_carac(map[index.y][index.x]))
			{
				return (index);
			}
			index.x++;
		}
		index.y++;
	}
	return (index);
}

t_pos	get_carac_pos(char **map, t_pos *offset)
{
	t_pos	index;

	index.x = 0;
	index.y = 0;
	while (map[index.y])
	{
		index.x = 0;
		while (map[index.y][index.x])
		{
			if (is_carac(map[index.y][index.x]))
			{
				carac_pos_update(offset, &index, map);
				index.x = index.x * TILE_SIZE + offset->x;
				index.y = index.y * TILE_SIZE + offset->y;
				return (index);
			}
			index.x++;
		}
		index.y++;
	}
	return (index);
}

int	check_colision(t_pos index, t_mlx *vars, char direction)
{
	if (direction == 'N')
		return (vars->map[index.y - 1][index.x] == '1' \
		&& vars->offset.y - PLAYER_SPEED < 0);
	if (direction == 'S')
		return (vars->map[index.y + 1][index.x] == '1' \
	&& vars->offset.y + PLAYER_SPEED > TILE_SIZE - (PLAYER_SIZE));
	if (direction == 'E')
		return (vars->map[index.y][index.x + 1] == '1' \
	&& vars->offset.x + PLAYER_SPEED > TILE_SIZE - (PLAYER_SIZE));
	if (direction == 'W')
		return (vars->map[index.y][index.x - 1] == '1' \
	&& vars->offset.x - PLAYER_SPEED < 0);
	return (0);
}

void	map(t_mlx *vars)
{
	if (vars->stats->map_is_create == 0)
	{
		vars->stats->map_is_create = 1;
		vars->stats->old_pos = get_carac_pos(vars->map, &vars->offset);
		draw_map(vars);
		init_mini_map(vars, get_carac_pos(vars->map, &vars->offset));
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win,
			 vars->mini_map.img, WIDTH - vars->mini_map.w - 100, 100);
	}
	if (vars->stats->old_pos.x != vars->offset.x \
	|| vars->stats->old_pos.y != vars->offset.y || vars->movement.rotating)
	{
        vars->stats->old_angle = vars->movement.rotating;
		vars->stats->old_pos.x = vars->offset.x;
		vars->stats->old_pos.y = vars->offset.y;
		init_mini_map(vars, get_carac_pos(vars->map, &vars->offset));
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win,
	 vars->mini_map.img, WIDTH - vars->mini_map.w - 100, 100);
	}
}

void	nfree(void *pointer)
{
	free(pointer);
	pointer = NULL;
}

int	main(int argc, char **argv)
{
	t_info	*info;
	t_mlx	vars;

	ft_memset(&vars, 0, sizeof(t_mlx));
	info = init_info();
	vars.mlx = mlx_init();
	vars.stats = info;
	info->display = &vars;
	if (!info)
		return (error_msg(E_MALLOC), 0);
	if (argc != 2)
		return (1);
	else
	{
		if (parsing_cube(argv[1], &vars.stats) == 0)
			return (1);
		else
			ft_printf("PARSING ✅\n");
	}
	vars.fps = 0;
	vars.offset.x = (TILE_SIZE >> 1) - (PLAYER_SIZE >> 1);
	vars.offset.y = TILE_SIZE >> 1;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH_WIN, HEIGHT_WIN, "Cube3D");
	vars.screen = new_img(&vars, WIDTH_WIN, HEIGHT_WIN);
	vars.img = new_img(&vars, WIDTH, HEIGHT);
	vars.overlay = new_file_img("texture/Overlay.xpm", &vars);
	gettimeofday(&vars.time, NULL);
	vars.map = info->map;
	vars.carac_index = get_carac_index(vars.map);
	vars.carac_pos = get_carac_pos(vars.map, &vars.offset);
    vars.movement.rotating = 0;
    vars.movement.rotation_speed = 1;
	ft_bzero(&vars.ray, sizeof(vars.ray));
     vars.ray.dir_x = 1;
     vars.ray.dir_y = 0;
   	vars.ray.plane_y = 0.66;
    vars.ray.plane_x = 0;
	map(&vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop_hook(vars.mlx, tick, &vars);
	mlx_loop(vars.mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	// t_color	pixel;
	// t_color colour = (t_color)(unsigned int)color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	// pixel = *(t_color *)dst;
	// float perc = colour.a / 255.;
	// pixel.r = pixel.r * perc + colour.r * (1 - perc);
	// pixel.g = pixel.g * perc + colour.g * (1 - perc);
	// pixel.b = pixel.b * perc + colour.b * (1 - perc);
	*(unsigned int *)dst = color;
}

t_tab_size	char_tab_len(char **tab)
{
	t_tab_size	size;

	size.row = 0;
	size.column = 0;
	while (tab[size.row])
	{
		size.row++;
	}
	while (tab[size.column])
	{
		size.column++;
	}
	return (size);
}

void	print_map(char **map)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (map[i][y])
	{
		while (map[i][y])
		{
			write(1, &map[i][y], 1);
			y++;
		}
		write(1, "\n", 1);
		i++;
		y = 0;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (((t & ((1 << 8) - 1))) << 24 | \
		(r & ((1 << 8) - 1)) << 16 | \
		(g & ((1 << 8) - 1)) << 8 | \
		(b & ((1 << 8) - 1)));
}

void	my_draw_line(t_pos origin, t_pos end, t_data *img)
{
	t_pos	delta_pos;
	float		mid;
	t_pos	current;

	current.x = origin.x;
	current.y = origin.y;
	delta_pos.x = end.x - origin.x;
	delta_pos.y = end.y - origin.y;
	mid = (float) delta_pos.y / delta_pos.x;
	while (current.x < end.x)
	{
		current.y = mid * (current.x - origin.x) + origin.y;
		my_mlx_pixel_put(img, current.x, current.y, 0xFFFFFFFF);
		current.x++;
	}
}

void	draw_line_from_mid(t_data *img, t_pos origin, int distance)
{
	t_pos	current;
	int		size;

	size = sqrt(distance);
	current.x = origin.x;
	current.y = origin.y;
	while (current.y < origin.y + size)
	{
		my_mlx_pixel_put(img, current.x, origin.y + (origin.y - current.y), \
		create_trgb(255, 255, 255, 255));
		my_mlx_pixel_put(img, current.x, current.y, \
		create_trgb(255, 255, 255, 255));
		current.y++;
	}
	while (current.y < HEIGHT)
	{
		my_mlx_pixel_put(img, current.x, origin.y + (origin.y - current.y), \
		SKY_COLOR);
		my_mlx_pixel_put(img, current.x, current.y, GROUND_COLOR);
		current.y++;
	}

}
