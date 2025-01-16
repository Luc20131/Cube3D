/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:11:37 by sjean             #+#    #+#             */
/*   Updated: 2025/01/16 14:13:09 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

u_int	find_pixel_color(t_pos *index, t_pos *size, t_pos *origin, t_mlx *vars)
{
	t_pos			map_size;
	unsigned int	color;

	map_size = size_map(vars->map);
	if (index->y == 0 || index->y == size->y - 1)
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

int	init_mini_map(t_mlx *vars)
{
	t_pos			size;
	t_pos			origin;
	t_data			*minimap;

	size.x = MINIMAP_SIZE * TILE_SIZE;
	size.y = MINIMAP_SIZE * TILE_SIZE;
	origin.x = vars->player_data.float_pos.x * TILE_SIZE \
		+ (PLAYER_SIZE >> 2) - (size.x >> 1);
	origin.y = vars->player_data.float_pos.y * TILE_SIZE \
		+ (PLAYER_SIZE >> 1) - (size.y >> 1);
	if (vars->layer[LAYER_MINIMAP].addr == NULL)
		vars->layer[LAYER_MINIMAP] = new_img(vars, size.x, size.y);
	minimap = &vars->layer[LAYER_MINIMAP];
	create_pixel(vars, &origin, &size, minimap);
	put_data_to_img(minimap, vars->layer[LAYER_MONITOR], 0, 0);
	draw_square(minimap, (t_pos){(size.x + PLAYER_SIZE) >> 1, \
		(size.y + PLAYER_SIZE) >> 1}, PLAYER_SIZE, 0xFF0FFF0F);
	return (1);
}
