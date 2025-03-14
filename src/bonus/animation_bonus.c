/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/19 09:45:48 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define ANIME_TIME	125

void	is_moving(t_mlx *vars)
{
	if (vars->player_data.movement.forward || \
		vars->player_data.movement.backward || \
		vars->player_data.movement.left || \
		vars->player_data.movement.right)
		vars->player_data.is_moving = 1;
	if (!vars->player_data.movement.forward && \
		!vars->player_data.movement.backward && \
		!vars->player_data.movement.left && \
		!vars->player_data.movement.right)
		vars->player_data.is_moving = 0;
}

t_data	*get_img_frame(t_mlx	*vars)
{
	static int				frame = 0;
	static struct timeval	tv;
	static int				time = 0;

	gettimeofday(&tv, 0);
	is_moving(vars);
	if (!vars->player_data.is_moving)
	{
		time = 0;
		return (&vars->anim[0]);
	}
	else
	{
		time = tv.tv_usec / 1000;
		frame = (time / ANIME_TIME) % 4;
		return (&vars->anim[frame]);
	}
}
