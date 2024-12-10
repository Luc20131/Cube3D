/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:24:21 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/28 12:27:57 by sjean            ###   ########.fr       */
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
	if (keycode == 65307)
	{
		exit_game(vars);
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

void	rotate_right(t_mlx *vars)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = vars->ray.dir.x;
	vars->ray.dir.x = vars->ray.dir.x * cos(-ROT_SPEED) \
	- vars->ray.dir.y * sin(-ROT_SPEED);
	vars->ray.dir.y = old_dir_x * sin(-ROT_SPEED) \
	+ vars->ray.dir.y * cos(-ROT_SPEED);
	old_plane_x = vars->ray.plane.x;
	vars->ray.plane.x = vars->ray.plane.x * cos(-ROT_SPEED) \
	- vars->ray.plane.y * sin(-ROT_SPEED);
	vars->ray.plane.y = old_plane_x * sin(-ROT_SPEED) \
	+ vars->ray.plane.y * cos(-ROT_SPEED);
}

void	rotate_left(t_mlx *vars)
{
	float	old_plane_x;
	float	old_dir_x;

	old_dir_x = vars->ray.dir.x;
	vars->ray.dir.x = vars->ray.dir.x * cos(ROT_SPEED) \
		- vars->ray.dir.y * sin(ROT_SPEED);
	vars->ray.dir.y = old_dir_x * sin(ROT_SPEED) \
		+ vars->ray.dir.y * cos(ROT_SPEED);
	old_plane_x = vars->ray.plane.x;
	vars->ray.plane.x = vars->ray.plane.x * cos(ROT_SPEED) \
		- vars->ray.plane.y * sin(ROT_SPEED);
	vars->ray.plane.y = old_plane_x * sin(ROT_SPEED) \
		+ vars->ray.plane.y * cos(ROT_SPEED);
}
