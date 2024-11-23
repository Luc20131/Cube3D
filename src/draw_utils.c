/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:34:16 by sjean             #+#    #+#             */
/*   Updated: 2024/11/23 18:50:59 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_darker_color(float coef, t_color *color)
{
	color->r *= coef;
	color->g *= coef;
	color->b *= coef;
}

int	init_pixel_tex_x(t_ray *ray, t_mlx *vars)
{
	int		tex_x;
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = vars->stats->img_texture[0].w \
	-(int)(wall_x * (double)(vars->stats->img_texture[0].w));
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = vars->stats->img_texture[0].w - tex_x;
	if (ray->side == 1 && ray->dir_y <= 0)
		tex_x = vars->stats->img_texture[0].w - tex_x;
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
