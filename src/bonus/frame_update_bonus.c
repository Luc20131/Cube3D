/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/22 13:54:38 by sjean            ###   ########.fr       */
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
		vars->stats->old_pos = vars->player_data.float_pos;
		if (draw_map(vars) == 1)
			exit_game(vars);
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
