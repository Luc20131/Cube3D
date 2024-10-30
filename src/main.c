/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:52:12 by lrichaud          #+#    #+#             */
/*   Updated: 2024/10/29 17:37:45 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <stdio.h>

#include "../headers/cube3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "../headers/parsing.h"
#include "../minilibx-linux/mlx_int.h"
#include "../minilibx-linux/mlx.h"
#include <sys/time.h>
#define SIZE_IMG 1024
#define SKY_COLOR 0xFF5EACFF
#define GROUND_COLOR 0xFF5E3B10
#define FOV 90

void	map(t_mlx *vars);
t_pos	get_carac_index(char **map);
int		check_colision(t_pos index, t_mlx *vars, char direction);

// int	fps_counter()
// {
// 	static int	frame_count;
// 	struct timeval time;

// 	gettimeofday(&time, NULL);
// }

int	key_released(int keycode, t_mlx *vars)
{
	if (keycode == 'a')
		vars->movement.left = 0;
	else if (keycode == 'd')
		vars->movement.right = 0;
	else if (keycode == 'w')
		vars->movement.up = 0;
	else if (keycode == 's')
		vars->movement.down = 0;
	return (0);
}

int	tick(t_mlx *vars)
{
	if (vars->movement.right && !check_colision(get_carac_index(vars->map), vars, 'E'))
		vars->offset.x += PLAYER_SPEED * (vars->movement.right + vars->movement.left);
	else if (vars->movement.left && !check_colision(get_carac_index(vars->map), vars, 'W'))
		vars->offset.x += PLAYER_SPEED * (vars->movement.right + vars->movement.left);
	if ( vars->movement.up && !check_colision(get_carac_index(vars->map), vars, 'N'))
		vars->offset.y += PLAYER_SPEED * (vars->movement.down + vars->movement.up);
	else if (vars->movement.down && !check_colision(get_carac_index(vars->map), vars, 'S'))
		vars->offset.y += PLAYER_SPEED * (vars->movement.down + vars->movement.up);
	map(vars);
	return (1);
}

int	key_hook( int keycode, t_mlx *vars)
{
	int	i;
	struct timeval timer;

	i = 0;
	if (keycode == 65307)
	{
		gettimeofday(&timer, NULL);
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
		printf("fps : %lu", vars->fps / (timer.tv_sec - vars->time.tv_sec));
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	else if (keycode == 'd')
	{
		vars->movement.right = 1;
	}
	else if (keycode == 'a')
	{
		vars->movement.left = -1;
	}
	else if (keycode == 's')
	{
		vars->movement.down = 1;
	}
	else if (keycode == 'w')
	{
		vars->movement.up = -1;
	}
	else if (keycode == 37)
	{
		printf("%d\n",keycode);
	}
	return (0);
}

void	wall(t_data *img, float distance)
{
	t_pos	pos;

	pos.y = SIZE_IMG >> 1;
	pos.x = 0;
	while (pos.x < SIZE_IMG)
	{
		if (pos.x > 650 && pos.x < 900)
			distance--;
		else
			distance++;
		draw_line_from_mid(img, pos, distance);
		pos.x++;
	}
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
			if (map[index.y][index.x] == 'N')
			{
				index.x = index.x;
				index.y = index.y;
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
			if (map[index.y][index.x] == 'N')
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
		return (vars->map[index.y - 1][index.x] == '1' && vars->offset.y - PLAYER_SPEED < 0);
	if (direction == 'S')
		return (vars->map[index.y + 1][index.x] == '1' && vars->offset.y + PLAYER_SPEED > TILE_SIZE - (PLAYER_SIZE));
	if (direction == 'E')
		return (vars->map[index.y][index.x + 1] == '1' && vars->offset.x + PLAYER_SPEED > TILE_SIZE - (PLAYER_SIZE));
	if (direction == 'W')
		return (vars->map[index.y][index.x - 1] == '1' && vars->offset.x - PLAYER_SPEED < 0);
	return (0);
}

void	map(t_mlx *vars)
{
	static int map_is_create = 0;
	static t_pos old_pos;

	
	if (map_is_create == 0)
	{
		map_is_create = 1;
		old_pos = get_carac_pos(vars->map, &vars->offset);
		map_gen(vars, vars->map);
		init_mini_map(vars, get_carac_pos(vars->map, &vars->offset));
		mlx_put_image_to_window(vars->mlx, vars->win, vars->mini_map.img, 100, 100);
		mlx_destroy_image(vars->mlx, vars->mini_map.img);
	}
	if (old_pos.x != vars->offset.x || old_pos.y != vars->offset.y)
	{
		old_pos.x = vars->offset.x;
		old_pos.y = vars->offset.y;
		init_mini_map(vars, get_carac_pos(vars->map, &vars->offset));
		mlx_put_image_to_window(vars->mlx, vars->win, vars->mini_map.img, 100, 100);
		mlx_destroy_image(vars->mlx, vars->mini_map.img);	
	}
  vars->fps++;
}

int	main(int argc, char **argv)
{
	// char	*map_line = "1111111111111111111111111\n1111111111111111111111111\n1111111111111111111111111\n1111111111111111111111111\n1100001111000011110000111\n1111001111110011111100111\n110000011100N001110000011\n1100000111000001110000011\n1101101111011011110110111\n1111111111111111111111111\n\0";
	t_info	*info;

	info = init_info();
	if (!info)
		return (error_msg(E_MALLOC), 0);
	if (argc != 2)
		return (1);
	else
	{
		if (parsing_cube(argv[1], &info) == 0)
			return (1);
		else
			ft_printf("PARSING ✅\n");
	}
	// exit(EXIT_SUCCESS);
	//*map[] = { "11111111", "10000001", "10110001", "10000001", "10101001", "11111111", "\0"};
	t_mlx	vars;

	vars.fps = 0;
	vars.offset.x = 0;
	vars.offset.y = 0;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Cube3D");
	vars.img = new_img(&vars, WIDTH, HEIGHT);
	vars.movement.up = 0;
	vars.movement.down = 0;
	vars.movement.left = 0;
	vars.movement.right = 0;
	gettimeofday(&vars.time, NULL);
	vars.map = info->map; //ft_split(map_line, '\n');
	map(&vars);
	// mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop_hook(vars.mlx, tick, &vars);
	mlx_loop(vars.mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
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
	int		mid;
	t_pos	current;

	current.x = origin.x;
	current.y = origin.y;
	delta_pos.x = end.x - origin.x;
	delta_pos.y = end.y - origin.y;
	mid = delta_pos.y / delta_pos.x;
	while (current.x < end.x)
	{
		current.y = mid * (current.x - origin.x) + origin.y;
		my_mlx_pixel_put(img, current.x, current.y, create_trgb(255, 255, 255, 255));
		current.x++;
	}

}

void	draw_horizon(t_data *img)
{
	int x;
	int y;
	int	color;

	x = 0;
	y = 0;
	color = create_trgb(255, 0, 170, 235);
	while (y < SIZE_IMG)
	{
		x = 0;
		while (x < SIZE_IMG)
		{
			if (y > SIZE_IMG / 2)
				color = create_trgb(255, 100, 20, 225);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
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
		my_mlx_pixel_put(img, current.x, origin.y + (origin.y - current.y), create_trgb(255, 255, 255, 255));
		my_mlx_pixel_put(img, current.x, current.y, create_trgb(255, 255, 255, 255));
		current.y++;
	}
	while (current.y < HEIGHT)
	{
		my_mlx_pixel_put(img, current.x, origin.y + (origin.y - current.y), SKY_COLOR);
		my_mlx_pixel_put(img, current.x, current.y, GROUND_COLOR);
		current.y++;
	}

}
