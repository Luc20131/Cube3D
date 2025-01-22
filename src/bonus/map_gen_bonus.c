/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/22 13:59:58 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	draw_map(t_mlx *game)
{
	int		k;
	t_pos	tab;
	t_pos	pos;
	t_pos	pos_;

	tab.y = -1;
	k = -1;
	start_tiles_init(game);
	if (autotile_generator(game->map, game) == 1)
		return (nfree(game->stats_tile), 1);
	game->layer[MAP] = new_img(game, game->size_map.x * TILE_SIZE, \
		game->size_map.y * TILE_SIZE);
	if (!game->layer[MAP].img)
		return (nfree(game->stats_tile), 1);
	while (++tab.y < game->size_map.y)
	{
		tab.x = -1;
		while (++tab.x < game->size_map.x)
		{
			pos_ = (t_pos){tab.x * TILE_SIZE, tab.y * TILE_SIZE};
			pos = tile_selector(game->tile, &game->stats_tile[++k]);
			img_cut(pos, game, pos_);
		}
	}
	return (0);
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
		color = get_pixel_img(&vars->layer[MAP], \
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
