/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:01:36 by lrichaud          #+#    #+#             */
/*   Updated: 2024/09/25 14:18:52 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float	ray_length(t_vector *vector)
{
	return (sqrtf((vector->delta_x * vector->delta_x) \
		+ (vector->delta_y * vector->delta_y)));
}

int	vector_init(t_posf posf, double angle, t_vector *vector)
{
	vector->origin = posf;
	vector->angle = angle;
	vector->length = 0;
	if (angle > 180.)
		vector->direction = -1;
	else
		vector->direction = 1;
	return (0);
}

int	raycast_one_vector(char **map)
{
	t_vector	vector;
	t_posf		pos;

	(void) map;
	pos.x = 1.;
	pos.y = 1.;
	vector_init(pos, 30., &vector);
	while (vector.length < 100.)
	{
		vector.length += 1.;
		vector.delta_x = vector.length * cos(vector.angle);
		vector.delta_y = vector.length * cos(180 - 90 - vector.angle);
		printf("%f, delta_x : %f delta_y : %f\n", vector.length, vector.delta_x, vector.delta_y);
	}
	return (0);
}
