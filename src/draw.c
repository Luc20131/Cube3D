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
	float	half_height;

	half_height = (vars->layer[LAYER_RAYCAST].h / 2.);
	(void)wall_top;
	while (current->y < wall_top->y)
	{
		pixel.x = 0xFF000030;
		coef = (1 - current->y / half_height);
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
	float	half_height;

	half_height = (1. / vars->layer[LAYER_RAYCAST].h);
	while (current->y < vars->layer[LAYER_RAYCAST].h)
	{
		pixel.x = 0xFF170501;
		coef = ((current->y - half_height) / half_height);
		if (ray->perp_wall_dist > 1)
			get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_wall(t_pos *current, t_mlx *vars, t_pos *end, t_data *img)
{
	t_posf	tex;
	t_color	pixel;
	const float		inverse_distance = (1. / vars->ray.perp_wall_dist);
	const int line_length = (vars->layer[LAYER_RAYCAST].line_length >> 2);
	const float step = ((float)img->h / (end->y - current->y));

	tex.x = init_pixel_tex_x(&vars->ray, vars) * img->pixels;
	tex.y = init_pixel_tex_y(current, step);
	while ((current->y < end->y) & (current->y < vars->layer[LAYER_RAYCAST].h))
	{
		tex.y += step;
		if (vars->ray.perp_wall_dist > 13)
			pixel.x = 0x00000000;
		else
		{
			pixel.x = *(unsigned int *)((img->addr + (int)tex.y * \
				img->line_length) + ((int)tex.x));
			if (vars->ray.side == 1)
				pixel.x = ((pixel.x >> 1) & 0x007F7F7F);
			if (vars->ray.perp_wall_dist > 1)
				get_darker_color(inverse_distance, &pixel);
		}
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		  line_length + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}
