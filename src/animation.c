/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/15 20:54:50 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <wait.h>
/* 1/8 s */
#define TAMAMAN	125

t_data	*get_img_frame(t_mlx	*vars)
{
	static int 				frame = 0;
	static struct timeval	tv;
	static int				time = 0;
	static int				old = 0;

	gettimeofday(&tv, 0);
	if (!vars->player_data.is_moving)
	{
		time = 0;
		return (&vars->animation[0]);
	}
	else
	{
		/*
		calcule le temps et le met dans un static qui se remet a zero quand 
		is_moving est a 0 ou qu'il a atteint le temps donner pour changer de 
		frame

		frame s'increment a chaque fois qu'il atteint le temps donne et retourne a
		0 quqnd il est au modulo du la taille de l'animation
		*/
		if (time <= TAMAMAN && old == 0)
		{
			old = 1;
			frame = (frame + 1) % 4;
		}
		if (time > TAMAMAN)
			old = 0;
		time = tv.tv_usec / 1000;

		return (&vars->animation[frame]);
	}
}
