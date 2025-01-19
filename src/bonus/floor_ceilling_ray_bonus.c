/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceilling_ray_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:32:36 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:45:48 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_and_display_pixel(t_mlx *vars, t_pos tex, t_pos end, int y)
{
	t_color			pixel;
	float			coef;
	static float	half_img;
	static int		line_length;
	const t_data	*img_raycast = &vars->layer[RAYCAST];

	line_length = img_raycast->line_length >> 2;
	half_img = img_raycast->h >> 1;
	if ((tex.x < vars->layer[FLOOR].w && tex.x > 0) || \
		(tex.y < vars->layer[FLOOR].h && tex.y > 0))
	{
		pixel.x = get_pixel_img(&vars->layer[FLOOR], tex.x, tex.y);
		coef = ((y - half_img) / (half_img)) / 3;
		if (vars->light)
			flashlight((t_pos){end.x, y}, &pixel);
		get_darker_color(coef, &pixel);
		((int *)img_raycast->addr) \
			[y * (line_length) + end.x] = pixel.x;
		((int *)img_raycast->addr) \
			[(img_raycast->h - y - 1) * line_length + end.x] = pixel.x;
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
		floor_tex.x = (int)(current_floor.x * vars->layer[FLOOR].w) \
										% vars->layer[FLOOR].w;
		floor_tex.y = (int)(current_floor.y * vars->layer[FLOOR].h) \
										% vars->layer[FLOOR].h;
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
