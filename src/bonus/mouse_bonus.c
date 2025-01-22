/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/19 09:45:48 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	event_mouse(int button, int x, int y, void *param)
{
	t_mlx	*vars;

	(void) x;
	(void) y;
	vars = param;
	if (button == 1)
	{
		mlx_mouse_hide(vars->mlx, vars->win);
		vars->mouse = 1;
	}
	else if (button == 3)
	{
		mlx_mouse_show(vars->mlx, vars->win);
		vars->mouse = 0;
	}
	return (1);
}

void	mouse_move(t_mlx *vars)
{
	t_pos	mouse_pos;

	if (!vars->mouse)
		return ;
	mlx_mouse_get_pos(vars->mlx, vars->win, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x > WIDTH)
	{
		rotate_right(vars);
		mlx_mouse_move(vars->mlx, vars->win, WIDTH, HEIGHT);
		raycast(vars);
	}
	else if (mouse_pos.x < WIDTH)
	{
		rotate_left(vars);
		mlx_mouse_move(vars->mlx, vars->win, WIDTH, HEIGHT);
		raycast(vars);
	}
	mlx_mouse_move(vars->mlx, vars->win, WIDTH, HEIGHT);
}

void	mouse_bonus(t_mlx *vars)
{
	mlx_mouse_hook(vars->win, event_mouse, vars);
}
