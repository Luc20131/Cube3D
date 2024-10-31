/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/10/31 15:43:55 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>
#include <stdio.h>


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

int	 	init_mini_map(t_mlx *vars,t_pos	carac_pos)
{
	t_data	mini_map_img;
	t_pos	index;
	t_pos	size;
	t_pos	origin;
	unsigned int	pixel;

	index.x = 0;
	index.y = 0;
	size.x = MINIMAP_SIZE * TILE_SIZE;
	size.y = MINIMAP_SIZE * TILE_SIZE;
	origin.x = carac_pos.x - ((size.x + PLAYER_SIZE) >> 1);
	origin.y = carac_pos.y - ((size.y + PLAYER_SIZE) >> 1);
	mini_map_img = new_img(vars, size.x, size.y);
	while (index.y < size.y)
	{
		index.x = 0;
		while (index.x < size.x)
		{
			if (index.y == 0 || index.y == size.y - 1)
				pixel = 0xFF3F3F3F;
			else if (origin.x + index.x < 0 || origin.y + index.y < 0)
				pixel = 0x00000000;
			else
				pixel = get_pixel_img(&vars->map_img, origin.x + index.x, origin.y + index.y);
			my_mlx_pixel_put(&mini_map_img, index.x, index.y, pixel);

			index.x++;
		}
		my_mlx_pixel_put(&mini_map_img, 0, index.y, 0xFF3F3F3F);
		my_mlx_pixel_put(&mini_map_img, index.x - 1, index.y, 0xFF3F3F3F);
		index.y++;
	}
	draw_square(&mini_map_img, (t_pos){(size.x + PLAYER_SIZE) / 2, (size.y + PLAYER_SIZE) / 2}, PLAYER_SIZE, 0xFF0FFF0F);
	vars->mini_map = mini_map_img;
	return (1);
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

void	carac_pos_update(t_pos *offset, t_pos *carac_pos, char **map)
{
	if (offset->x > TILE_SIZE && map[carac_pos->y][carac_pos->x + 1] != '1')
	{
		offset->x -= TILE_SIZE;
		map[carac_pos->y][carac_pos->x] = '0';
		map[carac_pos->y][++carac_pos->x] = 'N';
	}
	if (offset->y > TILE_SIZE && map[carac_pos->y + 1][carac_pos->x] != '1')
	{
		offset->y -= TILE_SIZE;
		map[carac_pos->y][carac_pos->x] = '0';
		map[++carac_pos->y][carac_pos->x] = 'N';
	}
	if (offset->x < 0 && map[carac_pos->y][carac_pos->x - 1] != '1')
	{
		offset->x += TILE_SIZE;
		map[carac_pos->y][carac_pos->x] = '0';
		map[carac_pos->y][--carac_pos->x] = 'N';
	}
	if (offset->y < 0 && map[carac_pos->y - 1][carac_pos->x] != '1')
	{
		offset->y += TILE_SIZE;
		map[carac_pos->y][carac_pos->x] = '0';
		map[--carac_pos->y][carac_pos->x] = 'N';
	}
}

int	map_gen(t_mlx *vars, char **map_tab)
{
	t_pos	index;
	t_pos	tiles_coords;
	t_pos	map_size;

	index.x = 0;
	index.y = 0;
	map_size = size_map(map_tab);
	vars->map_img = new_img(vars, map_size.x * TILE_SIZE, map_size.y * TILE_SIZE);
	while (index.y < map_size.y)
	{
		index.x = 0;
		tiles_coords.y = index.y * TILE_SIZE;
		while (index.x < map_size.x)
		{
			tiles_coords.x = index.x * TILE_SIZE;
			if (map_tab[index.y][index.x] == '1')
				draw_square(&vars->map_img, tiles_coords, TILE_SIZE, 255);
			else if (map_tab[index.y][index.x] == 'N')
				draw_square(&vars->map_img, tiles_coords, TILE_SIZE, 25);
			else
				draw_square(&vars->map_img, tiles_coords, TILE_SIZE, 25);
			index.x++;
		}
		index.y++;
	}
	return (0);
}
