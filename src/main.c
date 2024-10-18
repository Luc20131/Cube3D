/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:52:12 by lrichaud          #+#    #+#             */
/*   Updated: 2024/10/18 14:14:15 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../headers/cube3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <unistd.h>
#include "../headers/parsing.h"

#define SIZE_IMG 1024
#define WIDTH 1920
#define HEIGHT 1080
#define SKY_COLOR 0xFF5EACFF
#define GROUND_COLOR 0xFF5E3B10
#define FOV 90

// void	map_refresh(char **map)
// {
// 	return;
// }

int	key_hook(int keycode, t_mlx *vars)
{
	// int		size;
	// char	*map[] = { "11111111", "10000001", "10110001", "10000001", "10101001", "11111111", "\0"};

	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	// else if (keycode == 'd')
	// {
	// 	map_refresh();
	// }
	return (0);
}

void	wall(t_data *img, float distance)
{
	t_pos	pos;

	pos.y = SIZE_IMG / 2;
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

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	else
		parse_key(argv[1]);
	char	*map[] = {  "11111111",
						"11000011",
						"11110011",
						"1100N001",
						"11000001",
						"11011011",
						"11111111",
						"\0"};
	t_mlx	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Cube3D");
	vars.img = new_img(&vars, WIDTH, HEIGHT);
	map_gen(&vars, map);
	set_carac_pos(&vars, map);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.map_img.img, 100, 100);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
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
