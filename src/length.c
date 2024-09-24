/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:01:36 by lrichaud          #+#    #+#             */
/*   Updated: 2024/09/24 16:50:39 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>

float	ray_length(t_vector *vector)
{
	return (sqrtf((vector->delta_x * vector->delta_x) \
		+ (vector->delta_y * vector->delta_y)));
}

t_vector	vector_init(t_posf posf, float angle)
{
	t_vector vector;

	vector.origin = posf;

}
