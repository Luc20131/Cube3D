/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:52:29 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/06 06:14:25 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	put_data_to_img(t_data *dst, t_data src, int x, int y);

t_data	new_img(t_mlx *vars, unsigned int width, unsigned int height)
{
	t_data	frame;

	frame.img = mlx_new_image(vars->mlx, width, height);
	if (!frame.img)
		exit_game(vars);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, \
		&frame.line_length, &frame.endian);
	frame.h = height;
	frame.w = width;
	frame.pixels = frame.bits_per_pixel >> 3;
	frame.bits_per_line = frame.line_length >> 2;
	return (frame);
}

int	init_mini_map(t_mlx *vars)
{
	t_pos			index;
	t_pos			size;
	t_pos			origin;
	t_pos			map_size;
	unsigned int	pixel;
	t_data			*minimap;

	minimap = &vars->layer[LAYER_MINIMAP];
	index.x = 0;
	index.y = 0;
	size.x = MINIMAP_SIZE * TILE_SIZE;
	size.y = MINIMAP_SIZE * TILE_SIZE;
	origin.x = vars->player_data.float_pos.x * TILE_SIZE \
		+ (PLAYER_SIZE >> 2) - (size.x >> 1);
	origin.y = vars->player_data.float_pos.y * TILE_SIZE \
		+ (PLAYER_SIZE >> 1) - (size.y >> 1);
	if (minimap->addr == NULL)
		*minimap = new_img(vars, size.x, size.y);
	map_size = size_map(vars->map);
	while (index.y < size.y)
	{
		index.x = 0;
		while (index.x < size.x)
		{
			if (index.y == 0 || index.y == size.y - 1)
				pixel = 0xFF3F3F3F;
			else if (origin.x + index.x < 0 || origin.y + index.y < 0 \
				|| origin.x + index.x >= map_size.x * TILE_SIZE \
				|| origin.y + index.y >= map_size.y * TILE_SIZE)
				pixel = 0x00000000;
			else
			{
				pixel = get_pixel_img(&vars->layer[LAYER_MAP], \
					origin.x + index.x, origin.y + index.y);
			}
			((int *)minimap->addr)[index.y * minimap->bits_per_line + index.x] = pixel;
			index.x++;
		}
		((int *)minimap->addr)[index.y * minimap->bits_per_line + 0] = 0xFF3F3F3F;
		((int *)minimap->addr)[index.y * minimap->bits_per_line + index.x - 1] = 0xFF3F3F3F;
		index.y++;
	}
	put_data_to_img(minimap, vars->layer[LAYER_MONITOR], 0, 0);
	draw_square(minimap, (t_pos){(size.x + PLAYER_SIZE) >> 1, \
		(size.y + PLAYER_SIZE) >> 1}, PLAYER_SIZE, 0xFF0FFF0F);
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
			((int *)img->addr)[current.y * img->bits_per_line + current.x] = color;
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
		+ (x * img->pixels))));
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

void	player_pos_update(t_mlx *vars, char **map)
{
	static t_pos	old_pos = {0,0};
	t_posf			posf_player;

	posf_player = vars->player_data.float_pos;
	if (old_pos.x == 0 && old_pos.y == 0)
	{
		old_pos.x = (int)posf_player.x;
		old_pos.y = (int)posf_player.y;
	}
	if (map[old_pos.y][old_pos.x] != '1'
		&& map[(int)posf_player.y][(int)posf_player.x] != '1')
	{
		map[old_pos.y][old_pos.x] = '0';
		map[(int)posf_player.y][(int)posf_player.x] = 'N';
		old_pos.x = (int)posf_player.x;
		old_pos.y = (int)posf_player.y;
		vars->player_data.pixel_pos.x = TILE_SIZE * posf_player.x;
		vars->player_data.pixel_pos.y = TILE_SIZE * posf_player.y;
	}
}

t_data	new_file_img(char *path, t_mlx *vars)
{
	t_data	image;

	image.img = mlx_xpm_file_to_image(vars->mlx, path, &image.w, &image.h);
	if (!image.img)
	{
		printf("Error\nImage could not be read\n");
		exit(EXIT_FAILURE);
	}
	image.addr = mlx_get_data_addr(image.img, &(image.bits_per_pixel), \
		&(image.line_length), &(image.endian));
	image.pixels = image.bits_per_pixel >> 3;
	return (image);
}

void	put_pixel_img(t_data *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < img->w && y < img->h)
	{
		*(unsigned int *)(img->addr \
			+ (y * img->line_length + x * img->pixels)) = color;
	}
}

t_data	img_cut(t_pos pos, t_mlx *vars)
{
	t_sprite_slice	slice;
	int				j;
	int				i;

	slice = (t_sprite_slice){pos.y * TILE_SIZE, pos.x * TILE_SIZE, \
		TILE_SIZE, TILE_SIZE};
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			put_pixel_img(&vars->layer[LAYER_MINIMAP], j, i, \
				get_pixel_img(&vars->layer[LAYER_ACHANGER], slice.x + j, slice.y + i));
		}
	}
	return (vars->layer[LAYER_ACHANGER]);
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
	t_pos	pos;
	t_pos	map_size;

	j = -1;
	k = -1;
	start_tiles_init(game);
	autotile_generator(game->map, game);
	map_size = size_map(game->map);
	game->layer[LAYER_MAP] = new_img(game, map_size.x * TILE_SIZE, \
		map_size.y * TILE_SIZE);
	while (++j < map_size.y)
	{
		i = -1;
		while (++i < map_size.x)
		{
			pos = tile_selector(game->tile, &game->stats_tile[++k]);
			img_cut(pos, game);
		}
	}
}
