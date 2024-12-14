/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/14 20:01:44 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <wait.h>

t_data	get_img_frame(t_mlx	*vars)
{
	static int 		pos = 0;
	struct timeval	tv;

	if (!vars->player_data.is_moving)
		retrun (vars->animation[0]);
	else
	{
		gettimeofday(&tv, 0);
		/*
		calcule le temps et le met dans un static qui se remet a zero quand 
		is_moving est a 0 ou qu'il a atteint le temps donner pour changer de 
		frame

		pos s'increment a chaque fois qu'il atteint le temps donne et retourne a
		0 quqnd il est au modulo du la taille de l'animation
		*/
		return (vars->animation[pos]);
	}
}
