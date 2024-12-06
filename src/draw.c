/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2024/12/05 16:16:45 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top)
{
	t_color	pixel;
	float	coef;

	(void)current;
	(void)vars;
	(void)wall_top;
	while (current->y < wall_top->y)
	{
		pixel.x = 0xFF000030;
		coef = (1 - current->y / (vars->layer[LAYER_RAYCAST].h / 2.));
		get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_floor(t_pos *current, t_mlx *vars, t_ray *ray)
{
	t_color	pixel;
	float	coef;

	while (current->y < vars->layer[LAYER_RAYCAST].h)
	{
		pixel.x = 0xFF170501;
		coef = ((current->y - vars->layer[LAYER_RAYCAST].h / 2) / \
		(1. * (vars->layer[LAYER_RAYCAST].h / 2.)));
		if (ray->perp_wall_dist > 1)
			get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_wall(t_pos *current, t_mlx *vars, float step, t_pos *end)
{
	t_posf	tex;
	t_color	pixel;

	tex.x = init_pixel_tex_x(&vars->ray, vars);
	tex.y = init_pixel_tex_y(current, step);
	while (current->y < end->y && current->y < vars->layer[LAYER_RAYCAST].h)
	{
		tex.y += step;
		if (vars->ray.perp_wall_dist > 16)
			pixel.x = 0x00000000;
		else
		{
			pixel.x = get_pixel_img(&vars->stats->img_texture[0], tex.x, tex.y);
			if (vars->ray.side == 1)
				pixel.x = ((pixel.x >> 1) & 0x007F7F7F);
			if (vars->ray.perp_wall_dist > 2)
				get_darker_color(1./(vars->ray.perp_wall_dist / 2.), &pixel);
		}
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}
