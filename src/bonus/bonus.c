/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>                +#+  +:+       +#+  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/09 06:32:34 by lrichaud            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3d.h"

// void	init_bonus(t_mlx* vars)
// {
//
// }

char	*free_s2_to_join(const char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s2);
	return (temp);
}

void	fps(const t_mlx *vars)
{
	struct timeval	timer;
	struct timeval	total_time;
	char			*fps_string;

	gettimeofday(&timer, NULL);
	total_time.tv_usec = timer.tv_usec - vars->time.tv_usec;
	fps_string = ft_itoa(1000000 / total_time.tv_usec);
	fps_string = free_s2_to_join("fps : ", fps_string);
	mlx_string_put(vars->mlx, vars->win, 5, 10, 0x4200BB00, fps_string);
	free(fps_string);
}

void	flashlight(t_pos pixel_pos, t_color *color)
{
	unsigned int	distance_sqrt;
	unsigned int	color_overflow;
	const float		limit = HEIGHT * 185;
	distance_sqrt = ((unsigned int)(pixel_pos.y - (HEIGHT >> 1)) * ((unsigned int)(pixel_pos.y - (HEIGHT >> 1))) \
		+ (((unsigned int)(pixel_pos.x - (WIDTH >> 1)))) * ((unsigned int)(pixel_pos.x - (WIDTH >> 1))));
	if (distance_sqrt < limit)
	{
		if (distance_sqrt > (limit * 0.65))
		{
			color_overflow = color->b + (color->b * (limit - distance_sqrt) * (1./(limit * 0.25)));
			if (color_overflow < 200)
				color->b = color_overflow;
			color_overflow = color->g + (color->g * (limit - distance_sqrt) * (1./(limit * 0.25)) );
			if (color_overflow < 200)
				color->g = color_overflow;
			color_overflow = color->r + (color->r * (limit - distance_sqrt) * (1./(limit * 0.25)) );
			if (color_overflow < 200)
				color->r = color_overflow;
		}
		else
		{
			color_overflow = color->b + (color->b * (1./(limit * 0.25) * (limit * 0.35)));
			if (color_overflow < 200)
				color->b = color_overflow;
			color_overflow = color->g + (color->g * (1./(limit * 0.25) * (limit * 0.35)));
			if (color_overflow < 200)
				color->g = color_overflow;
			color_overflow = color->r + (color->r * (1./(limit * 0.25) * (limit * 0.35)));
			if (color_overflow < 200)
				color->r = color_overflow;
		}

	}
}
