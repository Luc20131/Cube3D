/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:34:16 by sjean             #+#    #+#             */
/*   Updated: 2024/11/29 15:19:01 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_data	select_texture(t_data img[4], t_mlx *vars)
{
	if (vars->ray.side == 1)
	{
		if (vars->ray.ray_dir_y > 0)
			return (img[NO]);
		else if (vars->ray.ray_dir_y < 0)
			return (img[SO]);
	}
	else if (vars->ray.ray_dir_x < 0)
		return (img[EA]);
	else if (vars->ray.ray_dir_x > 0)
		return (img[WE]);
	return (img[WE]);
}

void	get_darker_color(float coef, t_color *color)
{
	color->r *= coef;
	color->g *= coef;
	color->b *= coef;
}

int	init_pixel_tex_x(t_ray *ray, t_mlx *vars)
{
	int		tex_x;
	t_data	img_wall;

	img_wall = select_texture(vars->stats->img_texture, vars);
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	tex_x = img_wall.w -1 -(int)(ray->wall_x * (double)(img_wall.w));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = img_wall.w - (tex_x + 1);
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = img_wall.w - (tex_x + 1);
	return (tex_x);
}

float	init_pixel_tex_y(t_pos *current, double step)
{
	float	tex_y;

	tex_y = -step;
	if (current->y < 0)
	{
		tex_y = (step * (-1 * current->y));
		current->y = 0;
	}
	return (tex_y);
}
