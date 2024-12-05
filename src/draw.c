/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2024/11/28 14:26:18 by sjean            ###   ########.fr       */
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
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * (vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
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
		coef = ((current->y - vars->layer[LAYER_RAYCAST].h / 2) / (1. * (vars->layer[LAYER_RAYCAST].h / 2.)));
		if (ray->perp_wall_dist > 1)
			get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * (vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_wall(t_pos *current, t_mlx *vars, float step, t_pos *end)
{
	int		tex_x;
	float	tex_y;
	t_color	pixel;

	tex_x = init_pixel_tex_x(&vars->ray, vars);
	tex_y = init_pixel_tex_y(current, step);
	while (current->y < end->y && current->y < vars->layer[LAYER_RAYCAST].h)
	{
		tex_y += step;
		if (vars->ray.perp_wall_dist > 13)
			pixel.x = 0x00000000;
		else
		{
			pixel.x = get_pixel_img(&vars->stats->img_texture[0], tex_x, tex_y);
			if (vars->ray.side == 1)
				pixel.x = ((pixel.x >> 1) & 0x007F7F7F);
			if (vars->ray.perp_wall_dist > 1)
			{
				pixel.r /= (vars->ray.perp_wall_dist);
				pixel.g /= (vars->ray.perp_wall_dist);
				pixel.b /= (vars->ray.perp_wall_dist);
			}
		}
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * (vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}
