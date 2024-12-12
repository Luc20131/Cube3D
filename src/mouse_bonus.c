/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/15 07:56:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"

int	event_mouse(int button, int x, int y, void *param)
{
	t_mlx	*vars;
	(void) x;
	(void) y;
	vars = param;
	if (button == 1)
		mlx_mouse_hide(vars->mlx, vars->win);
	else if (button == 3)
		mlx_mouse_show(vars->mlx, vars->win);
	return (1);
}

void	mouse_move(t_mlx *vars)
{
	t_pos	mouse_pos;

	mlx_mouse_get_pos(vars->mlx, vars->win, &mouse_pos.x, &mouse_pos.y);
	if (mouse_pos.x > WIDTH_WIN >> 1)
	{
		rotate_right(vars);
		mlx_mouse_move(vars->mlx, vars->win, WIDTH_WIN >> 1, HEIGHT_WIN >> 1);
		map(vars);
	}
	else if (mouse_pos.x < WIDTH_WIN >> 1)
	{
		rotate_left(vars);
		mlx_mouse_move(vars->mlx, vars->win, WIDTH_WIN >> 1, HEIGHT_WIN >> 1);
		map(vars);
	}
	mlx_mouse_move(vars->mlx, vars->win, WIDTH_WIN >> 1, HEIGHT_WIN >> 1);
}

void	mouse_bonus(t_mlx *vars)
{
	mlx_mouse_hook(vars->win, event_mouse, vars);
}

