/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>                +#+  +:+       +#+  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/09 06:32:34 by lrichaud            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3d.h"

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
	unsigned int		distance_sqrt;
	const unsigned int	limit = HEIGHT * 180;
	const unsigned int	half_height = pixel_pos.y - (HEIGHT >> 1);
	const unsigned int	half_width = pixel_pos.x - (WIDTH >> 1);
	float				coef_limit;

	coef_limit = (1. / (limit >> 2));
	distance_sqrt = (half_height) * (half_height) + (half_width * half_width);
	if (distance_sqrt < limit)
	{
		if (distance_sqrt > (limit * 0.65))
		{
			coef_limit = (limit - distance_sqrt) * coef_limit;
			color->b = fmin(255, color->b + (color->b * coef_limit));
			color->g = fmin(255, color->g + (color->g * coef_limit));
			color->r = fmin(255, color->r + (color->r * coef_limit));
		}
		else
		{
			coef_limit = coef_limit * (limit * 0.35);
			color->b = fmin(255, color->b + (color->b * coef_limit));
			color->g = fmin(255, color->g + (color->g * coef_limit));
			color->r = fmin(255, color->r + (color->r * coef_limit));
		}
	}
}
