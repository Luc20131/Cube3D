/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:24:21 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/18 12:02:23 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key_released(const int keycode, t_mlx *vars)
{
	if (keycode == 'a')
		vars->player_data.movement.left = 0;
	else if (keycode == 'd')
		vars->player_data.movement.right = 0;
	else if (keycode == 'w')
		vars->player_data.movement.forward = 0;
	else if (keycode == 's')
		vars->player_data.movement.backward = 0;
    else if (keycode == 65363)
        vars->player_data.movement.rotating = 0;
    else if (keycode == 65361)
        vars->player_data.movement.rotating = 0;
    return (0);
}

int	key_hook(const int keycode, t_mlx *vars)
{
	int	i;

	i = 0;
	if (keycode == 65307)
	{
		fps(vars);
		mlx_do_key_autorepeaton(vars->mlx);
		while (vars->map[i])
			nfree(vars->map[i++]);
		nfree(vars->map);
		mlx_destroy_image(vars->mlx, vars->layer[LAYER_RAYCAST].img);
		mlx_destroy_image(vars->mlx, vars->layer[LAYER_SCREEN].img);
		mlx_destroy_image(vars->mlx, vars->layer[LAYER_MAP].img);
		mlx_destroy_image(vars->mlx, vars->layer[LAYER_MINIMAP].img);
		mlx_destroy_image(vars->mlx, vars->layer[LAYER_OVERLAY].img);
		mlx_destroy_image(vars->mlx, vars->stats->img_texture[0].img);
		mlx_destroy_image(vars->mlx, vars->stats->img_texture[1].img);
		mlx_destroy_image(vars->mlx, vars->stats->img_texture[2].img);
		mlx_destroy_image(vars->mlx, vars->stats->img_texture[3].img);
		// mlx_destroy_image(vars->mlx, vars->layer[LAYER_TILE_MAP].img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		nfree(vars->mlx);
		exit(1);
	}
	else if (keycode == 'd')
		vars->player_data.movement.right = 1;
	else if (keycode == 'a')
		vars->player_data.movement.left = -1;
	else if (keycode == 's')
		vars->player_data.movement.backward = -1;
	else if (keycode == 'w')
		vars->player_data.movement.forward = 1;
   	else if (keycode == 65363)
        vars->player_data.movement.rotating = -1;
    else if (keycode == 65361)
        vars->player_data.movement.rotating = 1;
    else
      printf("%i\n", keycode);
	return (0);
}
