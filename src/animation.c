/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/08 14:09:01 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <wait.h>
/* 1/8 s */
#define ANIME_TIME	125

t_data	*get_img_frame(t_mlx	*vars)
{
	static int 				frame = 0;
	static struct timeval	tv;
	static int				time = 0;

	gettimeofday(&tv, 0);
	if (!vars->player_data.is_moving)
	{
		time = 0;
		return (&vars->animation[0]);
	}
	else
	{
		time = tv.tv_usec / 1000;
		frame = (time / ANIME_TIME) % 4;
		return (&vars->animation[frame]);
	}
}
