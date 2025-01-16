/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_update_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/16 17:00:16 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3d.h"
#include "bonus.h"

void	map(t_mlx *vars)
{
	if (vars->stats->map_is_create == 0)
	{
		vars->stats->map_is_create = 1;
		vars->stats->old_pos = vars->player_data.float_pos;
		draw_map(vars);
		nfree(vars->stats_tile);
		init_mini_map(vars);
		raycast(vars);
	}
	else
	{
		vars->stats->old_angle = vars->player_data.movement.rotating;
		vars->stats->old_pos = vars->player_data.float_pos;
		init_mini_map(vars);
		raycast(vars);
	}
}

int	tick(t_mlx *vars)
{
	const int	minimap_offset = WIDTH_WIN - (TILE_SIZE * MINIMAP_SIZE) - 100;

	if (vars->player_data.movement.forward)
		collision(vars, vars->player_data.float_pos, (t_pos){1, 1}, 0);
	if (vars->player_data.movement.backward)
		collision(vars, vars->player_data.float_pos, (t_pos){-1, -1}, 0);
	if (vars->player_data.movement.right)
		collision(vars, vars->player_data.float_pos, (t_pos){-1, 1}, 1);
	if (vars->player_data.movement.left)
		collision(vars, vars->player_data.float_pos, (t_pos){1, -1}, 1);
	player_pos_update(vars, vars->map);
	map(vars);
	put_img_to_img(get_img_frame(vars), &vars->layer[LAYER_RAYCAST]);
	put_img_to_img(&vars->layer[LAYER_OVERLAY], &vars->layer[LAYER_RAYCAST]);
	upscale_rc_to_screen(&vars->layer[LAYER_RAYCAST], \
												&vars->layer[LAYER_SCREEN]);
	mlx_put_image_to_window(vars->mlx, vars->win, \
										vars->layer[LAYER_SCREEN].img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->layer[LAYER_MINIMAP].img, minimap_offset, 100);
	fps(vars);
	return (1);
}
