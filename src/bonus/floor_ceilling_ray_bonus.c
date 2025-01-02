/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceilling_ray_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:36 by sjean             #+#    #+#             */
/*   Updated: 2024/12/07 13:26:35 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3d.h"

void	get_and_display_pixel(t_mlx *vars, t_pos floor_tex, t_pos end, int y)
{
	t_color			pixel;
	float			coef;
	static float	half_img;
	static int		line_length;

	line_length = vars->layer[LAYER_RAYCAST].line_length >> 2;
	half_img = vars->layer[LAYER_RAYCAST].h >> 1;
	if ((floor_tex.x < vars->layer[LAYER_FLOOR].w && floor_tex.x > 0) || \
		(floor_tex.y < vars->layer[LAYER_FLOOR].h && floor_tex.y > 0))
	{
		pixel.x = get_pixel_img(&vars->layer[LAYER_FLOOR], floor_tex.x, floor_tex.y);
		coef = ((y - half_img) / (half_img)) / 3;
		if (vars->light)
			flashlight((t_pos){end.x, y}, &pixel);
		get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr) \
			[y * (line_length) + end.x] = pixel.x;
		((int *)vars->layer[LAYER_RAYCAST].addr)[(vars->layer[LAYER_RAYCAST].h - y - 1) * \
			line_length + end.x] = pixel.x;
	}
}

int	print_floor_ceilling(t_mlx *vars, t_ray *ray, t_pos *end)
{
	int		y;
	t_posf	current_floor;
	t_pos	floor_tex;
	float	weight;

	if (end->y < 0)
		end->y = HEIGHT;
	y = end->y -1;
	while (++y < HEIGHT)
	{
		ray->current_dist = HEIGHT / (2.0 * y - HEIGHT);
		weight = (ray->current_dist - ray->dist_player) / \
										(ray->dist_wall - ray->dist_player);
		current_floor.y = weight * ray->floor_wall.y + (0.5 - weight) * \
																	ray->pos.y;
		current_floor.x = weight * ray->floor_wall.x + (0.5 - weight) * \
																	ray->pos.x;
		floor_tex.x = (int)(current_floor.x * vars->layer[LAYER_FLOOR].w) \
										% vars->layer[LAYER_FLOOR].w;
		floor_tex.y = (int)(current_floor.y * vars->layer[LAYER_FLOOR].h) \
										% vars->layer[LAYER_FLOOR].h;
		get_and_display_pixel(vars, floor_tex, *end, y);
	}
	return (0);
}

int	vertical_raycast(t_mlx *vars, t_pos *end)
{
	if (vars->ray.side == 0 && vars->ray.ray_dir.x > 0)
	{
		vars->ray.floor_wall.x = vars->ray.map_pos.x;
		vars->ray.floor_wall.y = vars->ray.map_pos.y + vars->ray.wall_x;
	}
	else if (vars->ray.side == 0 && vars->ray.ray_dir.x < 0)
	{
		vars->ray.floor_wall.x = vars->ray.map_pos.x + 1.0;
		vars->ray.floor_wall.y = vars->ray.map_pos.y + vars->ray.wall_x;
	}
	else if (vars->ray.side == 1 && vars->ray.ray_dir.y > 0)
	{
		vars->ray.floor_wall.x = vars->ray.map_pos.x + vars->ray.wall_x;
		vars->ray.floor_wall.y = vars->ray.map_pos.y;
	}
	else
	{
		vars->ray.floor_wall.x = vars->ray.map_pos.x + vars->ray.wall_x;
		vars->ray.floor_wall.y = vars->ray.map_pos.y + 1.0;
	}
	vars->ray.dist_wall = vars->ray.perp_wall_dist;
	vars->ray.dist_player = 0.0;
	print_floor_ceilling(vars, &vars->ray, end);
	return (0);
}
