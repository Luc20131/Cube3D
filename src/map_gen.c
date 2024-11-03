/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/03 18:56:35 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>
#include <stdio.h>

void	put_data_to_img(t_data dst, t_data src, int x, int y);

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
	t_pos	index;
	t_pos	size;
	t_pos	origin;
	t_pos	map_size;
	unsigned int	pixel;
	t_data	monitoring;

	index.x = 0;
	index.y = 0;
	size.x = MINIMAP_SIZE * TILE_SIZE;
	size.y = MINIMAP_SIZE * TILE_SIZE;
	origin.x = carac_pos.x - ((size.x + PLAYER_SIZE) >> 1);
	origin.y = carac_pos.y - ((size.y + PLAYER_SIZE) >> 1);
	if (vars->mini_map.img == NULL)
		vars->mini_map = new_img(vars, size.x, size.y);
	map_size = size_map(vars->map);
	while (index.y < size.y)
	{
		index.x = 0;
		while (index.x < size.x)
		{
			if (index.y == 0 || index.y == size.y - 1)
				pixel = 0xFF3F3F3F;
			else if (origin.x + index.x < 0 || origin.y + index.y < 0 ||
			origin.x + index.x >= map_size.x * TILE_SIZE || origin.y + index.y >= map_size.y * TILE_SIZE)
				pixel = 0x00000000;
			else
				pixel = get_pixel_img(&vars->map_img, origin.x + index.x, origin.y + index.y);
			my_mlx_pixel_put(&vars->mini_map, index.x, index.y, pixel);

			index.x++;
		}
		my_mlx_pixel_put(&vars->mini_map, 0, index.y, 0xFF3F3F3F);
		my_mlx_pixel_put(&vars->mini_map, index.x - 1, index.y, 0xFF3F3F3F);
		index.y++;
	}
	monitoring = new_file_img("texture/monitoring.xpm", vars);
	put_data_to_img(vars->mini_map, monitoring, 0 * TILE_SIZE, 0 * TILE_SIZE);
	draw_square(&vars->mini_map, (t_pos){(size.x + PLAYER_SIZE) / 2, (size.y + PLAYER_SIZE) / 2}, PLAYER_SIZE, 0xFF0FFF0F);
	vars->mini_map = vars->mini_map;
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

t_data	new_file_img(char *path, t_mlx *window)
{
	t_data	image;

	image.img = mlx_xpm_file_to_image(window->mlx, path, &image.w, &image.h);
	if (!image.img)
		write(2, "Error\nFile could not be read\n", 29);
	else
		image.addr = mlx_get_data_addr(image.img, &(image.bits_per_pixel), \
			&(image.line_length), &(image.endian));
	return (image);
}

void	pixel_img(t_data img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

t_data	img_cut(char *path, t_pos pos, t_mlx *g)
{
	t_sprite_slice	slice;
	t_data			img;
	t_data			source;
	int				j;
	int				i;

	slice = (t_sprite_slice){pos.y * TILE_SIZE, pos.x * TILE_SIZE,\
	 TILE_SIZE, TILE_SIZE};
	img = new_img(g, slice.width, slice.height);
	source = new_file_img(path, g);
	i = -1;
	while (++i < slice.width)
	{
		j = -1;
		while (++j < slice.height)
		{
			pixel_img(img, j, i, \
				get_pixel_img(&source, slice.x + j, slice.y + i));
		}
	}
	mlx_destroy_image(g->mlx, source.img);
	return (img);
}

static int	put_pixel_valid(t_data img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		return (*(unsigned int *)(img.addr + \
		(y * img.line_length + x * (img.bits_per_pixel / 8))) != 0xFF000000 && \
		*(unsigned int *)(img.addr + \
		(y * img.line_length + x * (img.bits_per_pixel / 8))) != 0x00000000);
	}
	return (0);
}

void	put_data_to_img(t_data dst, t_data src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			if (put_pixel_valid(src, i, j))
				pixel_img(dst, x + i, y + j, get_pixel_img(&src, i, j));
			j++;
		}
		i++;
	}
}

t_pos	tile_selector(t_tile tile[49], int *stats)
{
	int		i;

	i = -1;
	while (++i < 50)
	{
		if (*stats == tile[i].dir)
		{
			return (tile[i].pos);
		}
	}
	return (tile[47].pos);
}

void	draw_map(t_mlx *game)
{
	int		i;
	int		j;
	int		k;
	t_data	img;
	t_pos	pos;
	t_pos	map_size;

	j = -1;
	k = -1;
	start_tiles_init(game);
	autotile_generator(game->map, game);
	map_size = size_map(game->map);
 	game->map_img = new_img(game, map_size.x * TILE_SIZE, map_size.y * TILE_SIZE);
	while (++j < map_size.y)
	{
		i = -1;
		while (++i < map_size.x)
		{
			pos = tile_selector(game->tile, &game->stats_tile[++k]);
			img = img_cut("texture/SusMap.xpm", pos, game);
			put_data_to_img(game->map_img, img, i * TILE_SIZE, j * TILE_SIZE);
			mlx_destroy_image(game->mlx, img.img);
		}
	}
}
