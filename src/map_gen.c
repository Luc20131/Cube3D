/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/10/18 14:11:26 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>
#include <stdio.h>
#define HEIGHT 1024
#define WIDTH 1024
#define TILE_SIZE 32

t_data	new_img(t_mlx *vars, unsigned int width, unsigned int height)
{
	t_data	frame;

	frame.img = mlx_new_image(vars->mlx, width, height);
	if (!frame.img)
	{
		frame.addr = NULL;
		return (frame);
	}
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, \
		&frame.line_length, &frame.endian);
	frame.h = height;
	frame.w = width;
	return (frame);
}

void	draw_square(t_data *img, t_pos origin, int size, int color)
{
	t_pos	current;

	current.x = origin.x;
	current.y = origin.y;
	while (current.x < origin.x + size)
	{
		current.y = origin.y;
		while (current.y < origin.y + size)
		{
			my_mlx_pixel_put(img, current.x, current.y, create_trgb(250, 100, color, 100));
			current.y++;
		}
		current.x++;
	}
}

t_pos	size_map(char **map)
{
	t_pos	size;
	size_t	i;

	i = 0;
	while (map[i][0] != '\0')
		i++;
	size.y = i;
	size.x = (ft_strlen(map[0]));
	return (size);
}

unsigned int	get_pixel_img(t_data *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->line_length) \
		+ (x * img->bits_per_pixel / 8))));
}

void	print_tile_to_image(t_data *img, int tile_x, int tile_y)
{
	size_t	y;
	size_t	x;
	size_t	tile_size;
	size_t	sup;

	sup = 0;
	tile_size = TILE_SIZE;
	y = 0;
	while (y < tile_size)
	{
		x = -1;
		while (++x < tile_size)
			my_mlx_pixel_put(img, ((tile_x - sup) * tile_size) + x, ((tile_y \
			- sup) * tile_size) + y, get_pixel_img(img, x, y));
		y++;
	}
}

int	map_gen(t_mlx *vars, char **map_tab)
{
	t_pos	index;
	t_pos	tiles_coords;
	t_pos	map_size;
	// t_pos	pos_carac;

	index.x = 0;
	index.y = 0;
	map_size = size_map(map_tab);
	printf("%d %d\n",map_size.x, map_size.y);
	vars->map_img = new_img(vars, HEIGHT, WIDTH);
	while (index.y < map_size.y)
	{
		index.x = 0;
		while (index.x < map_size.x)
		{
			printf("%c", map_tab[index.y][index.x]);
			tiles_coords.x = index.x * TILE_SIZE;
			tiles_coords.y = index.y * TILE_SIZE;
			if (map_tab[index.y][index.x] == '1')
				draw_square(&vars->map_img, tiles_coords, 64, 0);
			else if (map_tab[index.y][index.x] == 'N')
			{
				draw_square(&vars->map_img, tiles_coords, 64, 125);
			}
			else
				draw_square(&vars->map_img, tiles_coords, 64, 125);
			index.x++;
		}
		printf("\n");
		index.y++;
	}
	return (0);
}
