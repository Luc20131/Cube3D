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
