/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/15 07:56:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"

void	map(t_mlx *vars)
{
	const int	minimap_offset = WIDTH_WIN - (TILE_SIZE * MINIMAP_SIZE) - 100;

	if (vars->stats->map_is_create == 0)
	{
		vars->stats->map_is_create = 1;
		vars->stats->old_pos = vars->player_data.float_pos;
		draw_map(vars);
		nfree(vars->stats_tile);
		init_mini_map(vars);
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->layer[LAYER_MINIMAP].img, minimap_offset, 100);
	}
	// else if (vars->stats->old_pos.x != vars->player_data.float_pos.x
	// 	|| vars->stats->old_pos.y != vars->player_data.float_pos.y
	// 	|| vars->player_data.movement.rotating)
	else
	{
		gettimeofday(&vars->time, NULL);
		vars->stats->old_angle = vars->player_data.movement.rotating;
		vars->stats->old_pos = vars->player_data.float_pos;
		init_mini_map(vars);
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->layer[LAYER_MINIMAP].img, minimap_offset, 100);
	}
}

int	tick(t_mlx *vars)
{
	if (vars->player_data.movement.forward)
	{
		vars->player_data.float_pos.x += (PLAYER_SPEED * vars->ray.dir.x);
		vars->player_data.float_pos.y += (PLAYER_SPEED * vars->ray.dir.y);
	}
	else if (vars->player_data.movement.backward)
	{
		vars->player_data.float_pos.x -= (PLAYER_SPEED * vars->ray.dir.x);
		vars->player_data.float_pos.y -= (PLAYER_SPEED * vars->ray.dir.y);
	}
	else if (vars->player_data.movement.right)
	{
		vars->player_data.float_pos.x -= (PLAYER_SPEED * vars->ray.dir.y);
		vars->player_data.float_pos.y += (PLAYER_SPEED * vars->ray.dir.x);
	}
	else if (vars->player_data.movement.left)
	{
		vars->player_data.float_pos.x += (PLAYER_SPEED * vars->ray.dir.y);
		vars->player_data.float_pos.y -= (PLAYER_SPEED * vars->ray.dir.x);
	}
	player_pos_update(vars, vars->map);
	mouse_move(vars);
	map(vars);
	fps(vars);
	return (1);
}

u_int	find_pixel_color(t_pos *index, t_pos *size, t_pos *origin, t_mlx *vars)
{
	t_pos			map_size;
	unsigned int	color;

	map_size = size_map(vars->map);
	if (index->y == 0 || index->y == size->y - 1)
		color = 0x003F3F3F;
	else if (index->x < origin->x || index->y < origin->y \
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

	minimap = &vars->layer[LAYER_MINIMAP];
	size.x = MINIMAP_SIZE * TILE_SIZE;
	size.y = MINIMAP_SIZE * TILE_SIZE;
	origin.x = vars->player_data.float_pos.x * TILE_SIZE \
		+ (PLAYER_SIZE >> 2) - (size.x >> 1);
	origin.y = vars->player_data.float_pos.y * TILE_SIZE \
		+ (PLAYER_SIZE >> 1) - (size.y >> 1);
	if (minimap->addr == NULL)
		*minimap = new_img(vars, size.x, size.y);
	create_pixel(vars, &origin, &size, minimap);
	put_data_to_img(minimap, vars->layer[LAYER_MONITOR], 0, 0);
	draw_square(minimap, (t_pos){(size.x + PLAYER_SIZE) >> 1, \
		(size.y + PLAYER_SIZE) >> 1}, PLAYER_SIZE, 0xFF0FFF0F);
	return (1);
}