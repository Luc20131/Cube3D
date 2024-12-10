/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
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
	else if (vars->stats->old_pos.x != vars->player_data.float_pos.x
		|| vars->stats->old_pos.y != vars->player_data.float_pos.y \
		|| vars->player_data.movement.rotating)
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
	map(vars);
	return (1);
}
