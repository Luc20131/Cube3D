/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/09/23 10:34:19 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <stdio.h>
#define HEIGHT 1024
#define WIDTH 1024
#define TILE_SIZE 64

t_data	new_img_not_square(t_mlx *vars, int height, int width)
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
	return (frame);
}

void	draw_square(t_data *img, t_pos origin, int size, int color)
{
	t_pos	current;

	current.x = origin.x;
	current.y = origin.y;
	while (current.y < origin.y + size)
	{
		current.x = origin.x;
		while (current.x < origin.x + size)
		{
			my_mlx_pixel_put(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
}

t_pos	size_map(char **map)
{
	t_pos	size;
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	size.y = i;
	size.x = (ft_strlen(map[0]) - 1);
	return (size);
}

unsigned int	get_pixel_img(t_data img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_length) \
		+ (x * img.bits_per_pixel / 8))));
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
			- sup) * tile_size) + y, get_pixel_img(*img, x, y));
		y++;
	}
}

int	map_gen(t_mlx *vars, char **map_tab)
{
	t_data	map_img;
	t_pos	index;
	t_pos	tiles_coords;
	t_pos	map_size;

	index.x = 0;
	index.y = 0;
	map_size = size_map(map_tab);
	map_img = new_img_not_square(vars, HEIGHT, WIDTH);
	while (index.y < map_size.y- 1)
	{
		index.x = 0;
		while (index.x < map_size.x - 1)
		{
			tiles_coords.x = index.x * TILE_SIZE;
			tiles_coords.y = index.y * TILE_SIZE;
			if (map_tab[index.y][index.x] == 1)
				draw_square(&map_img, tiles_coords, 64, create_trgb(255, 200, 50, 50));
			else
				draw_square(&map_img, tiles_coords, 64, create_trgb(255, 50, 50, 50));
			index.x++;
		}
		index.y++;
	}
	return (0);
}
