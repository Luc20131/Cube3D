/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:24:21 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/18 12:02:23 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key_released(int keycode, t_mlx *vars)
{
	if (keycode == 'a')
		vars->movement.left = 0;
	else if (keycode == 'd')
		vars->movement.right = 0;
	else if (keycode == 'w')
		vars->movement.forward = 0;
	else if (keycode == 's')
		vars->movement.backward = 0;
    else if (keycode == 65363)
        vars->movement.rotating = 0;
    else if (keycode == 65361)
        vars->movement.rotating = 0;
    return (0);
}

void	fps(t_mlx *vars)
{
	struct timeval timer;

	gettimeofday(&timer, NULL);
	printf("fps : %lu", vars->fps / (timer.tv_sec - vars->time.tv_sec));
}

int	key_hook( int keycode, t_mlx *vars)
{
	int	i;

	i = 0;
	if (keycode == 65307)
	{
		fps(vars);
		mlx_do_key_autorepeaton(vars->mlx);
		while (vars->map[i])
			nfree(vars->map[i++]);
		nfree(vars->map);
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		nfree(vars->mlx);
		exit(1);
	}
	else if (keycode == 'd')
		vars->movement.right = 1;
	else if (keycode == 'a')
		vars->movement.left = -1;
	else if (keycode == 's')
		vars->movement.backward = -1;
	else if (keycode == 'w')
		vars->movement.forward = 1;
   	else if (keycode == 65363)
        vars->movement.rotating = -1;
    else if (keycode == 65361)
        vars->movement.rotating = 1;
    else
      printf("%i\n", keycode);
	return (0);
}
