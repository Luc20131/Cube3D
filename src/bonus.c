/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>                +#+  +:+       +#+  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/09 06:32:34 by lrichaud            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	mlx_string_put(vars->mlx, vars->win, 5, 10, 0x00AAAAAA, fps_string);
	free(fps_string);
}
