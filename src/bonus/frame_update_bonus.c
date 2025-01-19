/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/19 09:45:48 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	map(t_mlx *vars)
{
	const int	minimap_offset = WIDTH_WIN - (TILE_SIZE * MINIMAP_SIZE) - 100;

	gettimeofday(&vars->time, NULL);
	if (vars->stats->map_is_create == 0)
	{
		vars->stats->map_is_create = 1;
		draw_map(vars);
		nfree(vars->stats_tile);
		vars->layer[MINIMAP] = new_img(vars, MINIMAP_SIZE * TILE_SIZE, \
			MINIMAP_SIZE * TILE_SIZE);
		init_mini_map(vars);
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->layer[MINIMAP].img, minimap_offset, 100);
	}
	else
	{
		init_mini_map(vars);
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->layer[MINIMAP].img, minimap_offset, 100);
	}
	fps(vars);
}

void	collision(t_mlx *vars, t_posf pos, t_pos dir, int axe)
{
	if (axe == 0)
	{
		if (vars->map[(int)pos.y]
			[(int)(pos.x + (PLAYER_SPEED * vars->ray.dir.x) * dir.x)] != '1')
			vars->player_data.float_pos.x += (PLAYER_SPEED \
				* vars->ray.dir.x) * dir.x;
		if (vars->map[(int)(pos.y + (PLAYER_SPEED \
			* vars->ray.dir.y) * dir.y)] \
			[(int)pos.x] != '1')
			vars->player_data.float_pos.y += (PLAYER_SPEED \
				* vars->ray.dir.y) * dir.y;
	}
	else if (axe == 1)
	{
		if (vars->map[(int)pos.y]
			[(int)(pos.x + (PLAYER_SPEED * vars->ray.dir.y) * dir.x)] != '1')
			vars->player_data.float_pos.x += (PLAYER_SPEED \
				* vars->ray.dir.y) * dir.x;
		if (vars->map[(int)(pos.y + (PLAYER_SPEED * vars->ray.dir.x) * dir.y)] \
		[(int)pos.x] != '1')
			vars->player_data.float_pos.y += (PLAYER_SPEED \
				* vars->ray.dir.x) * dir.y;
	}
}

int	tick(t_mlx *vars)
{
	mouse_bonus(vars);
	if (vars->player_data.movement.forward)
	{
		collision(vars, vars->player_data.float_pos, (t_pos){1, 1}, 0);
	}
	if (vars->player_data.movement.backward)
	{
		collision(vars, vars->player_data.float_pos, (t_pos){-1, -1}, 0);
	}
	if (vars->player_data.movement.right)
	{
		collision(vars, vars->player_data.float_pos, (t_pos){-1, 1}, 1);
	}
	if (vars->player_data.movement.left)
	{
		collision(vars, vars->player_data.float_pos, (t_pos){1, -1}, 1);
	}
	player_pos_update(vars, vars->map);
	map(vars);
	return (1);
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
	minimap = &vars->layer[MINIMAP];
	create_pixel(vars, &origin, &size, minimap);
	put_data_to_img(minimap, vars->layer[MONITOR], 0, 0);
	draw_square(minimap, (t_pos){(size.x - PLAYER_SIZE) >> 1, \
		(size.y - PLAYER_SIZE) >> 1}, PLAYER_SIZE, 0xFF0FFF0F);
	return (1);
}
