/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/13 14:16:47 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
			put_pixel_img(img, current.x, current.y, color);
			current.x++;
		}
		current.y++;
	}
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
			((int *)img->addr)[(((tile_y - sup) * tile_size) + y) * \
				(img->line_length >> 2) + (((tile_x - sup) * tile_size) \
					+ x)] = get_pixel_img(img, x, y);
		y++;
	}
}

void	draw_map(t_mlx *game)
{
	int		i;
	int		j;
	int		k;
	t_pos	pos;
	t_pos	pos_;

	j = -1;
	k = -1;
	start_tiles_init(game);
	autotile_generator(game->map, game);
	game->layer[LAYER_MAP] = new_img(game, game->size_map.x * TILE_SIZE, \
		game->size_map.y * TILE_SIZE);
	while (++j < game->size_map.y)
	{
		i = -1;
		while (++i < game->size_map.x)
		{
			pos_ = (t_pos){i * TILE_SIZE, j * TILE_SIZE};
			pos = tile_selector(game->tile, &game->stats_tile[++k]);
			img_cut(pos, game, pos_);
		}
	}
}

u_int	find_pixel_color(t_pos *index, t_pos *size, t_pos *origin, t_mlx *vars)
{
	t_pos			map_size;
	unsigned int	color;

	map_size = size_map(vars->map);
	if (index->y == 0 || index->y == size->y - 1 \
		|| index->x == 0 || index->x == size->y - 1)
		color = 0x003F3F3F;
	else if (origin->x + index->x < 0 || origin->y + index->y < 0 \
		|| origin->x + index->x >= map_size.x * TILE_SIZE \
		|| origin->y + index->y >= map_size.y * TILE_SIZE)
		color = 0x00000000;
	else
	{
		color = get_pixel_img(&vars->layer[LAYER_MAP], \
			origin->x + index->x, origin->y + index->y);
	}
	return (color);
}

void	create_pixel(t_mlx *vars, t_pos *origin, t_pos *size, t_data *minimap)
{
	t_pos			index;
	unsigned int	pixel;

	index.y = 0;
	while (index.y < size->y)
	{
		index.x = 0;
		while (index.x < size->x)
		{
			pixel = find_pixel_color(&index, size, origin, vars);
			put_pixel_img(minimap, index.x, index.y, pixel);
			index.x++;
		}
		put_pixel_img(minimap, origin->x, origin->y, 0xFF3F3F3F);
		put_pixel_img(minimap, index.x, index.y, 0x003F3F3F);
		index.y++;
	}
}
