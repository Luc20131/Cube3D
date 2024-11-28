/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2024/11/27 19:23:01 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_data select_texture(t_data img[4], t_mlx *vars)
{
	if (vars->ray.side == 1)
	{
		if (vars->ray.ray_dir_y > 0)
			return (img[NO]);
		else if (vars->ray.ray_dir_y < 0)
			return (img[SO]);
	}
	else if (vars->ray.ray_dir_x < 0)
			return (img[WE]);
	else if (vars->ray.ray_dir_x > 0)
			return (img[EA]);
	return (img[EA]);
}

int	print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top)
{
	t_color	pixel;
	float	coef;

	while (current->y < wall_top->y)
	{
		pixel.x = 0xFF000030;
		coef = (1 - current->y / (vars->img.h / 2.));
		get_darker_color(coef, &pixel);
		my_mlx_pixel_put(&vars->img, current->x, current->y, pixel.x);
		current->y++;
	}
	return (0);
}

int	print_floor(t_pos *current, t_mlx *vars, t_ray *ray)
{
	t_color	pixel;
	float	coef;

	while (current->y < vars->img.h)
	{
		pixel.x = 0xFF170501;
		coef = ((current->y - vars->img.h / 2) / (1. * (vars->img.h / 2.)));
		if (ray->perp_wall_dist > 1)
			get_darker_color(coef, &pixel);
		my_mlx_pixel_put(&vars->img, current->x, current->y, pixel.x);
		current->y++;
	}
	return (0);
}

int	print_wall(t_pos *current, t_mlx *vars, double step, t_pos *end)
{
	int		tex_x;
	float	tex_y;
	t_color	pixel;
	t_data	img_wall;

	tex_x = init_pixel_tex_x(&vars->ray, vars);
	tex_y = init_pixel_tex_y(current, step);
	while (current->y < end->y && current->y < vars->img.h)
	{
		tex_y += step;
		img_wall = select_texture(vars->stats->img_texture, vars);
		pixel.x = get_pixel_img(&img_wall, tex_x, tex_y);
		if (vars->ray.side == 1)
			pixel.x = ((pixel.x >> 1) & 0x007F7F7F);
		if (vars->ray.perp_wall_dist > 1)
		{
			pixel.r /= (vars->ray.perp_wall_dist);
			pixel.g /= (vars->ray.perp_wall_dist);
			pixel.b /= (vars->ray.perp_wall_dist);
		}
		my_mlx_pixel_put(&vars->img, current->x, current->y, pixel.x);
		current->y++;
	}
	return (0);
}
