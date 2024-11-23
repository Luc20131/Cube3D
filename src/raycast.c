/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/23 19:48:32 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>

#define PIX_PER_RAY 1

void	side_dist_and_stepper(t_ray	*ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_pos.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_pos.x + 1.0 - ray->pos_x) \
		* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_pos.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_pos.y + 1.0 - ray->pos_y) \
		* ray->delta_dist_y;
	}
}

int	print_display_from_ray(t_pos *wall_top, t_pos *end, t_mlx *vars, t_ray *ray)
{
	t_pos	current;
	double	step;

	current.x = wall_top->x;
	current.y = 0;
	if (current.y >= wall_top->y)
		current.y = wall_top->y;
	step = (1.0 * vars->stats->img_texture[0].h / (end->y - wall_top->y));
	print_ceilling(&current, vars, wall_top);
	print_wall(&current, vars, step, end);
	print_floor(&current, vars, ray);
	return (0);
}

int	one_cast(t_ray *ray, t_mlx *vars)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_pos.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_pos.y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map[ray->map_pos.y][ray->map_pos.x] > '0')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->end_ray.y = (int) ray->delta_dist_y * ray->dir_y;
	ray->end_ray.x = (int) ray->delta_dist_x * ray->dir_y;
	return (0);
}

void	wall_printer_from_cast(t_ray *ray, t_mlx *vars, t_pos *wall_top)
{
	int		line_height;
	t_pos	end;
	int		i;

	i = 0;
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.001;
	line_height = (int)(vars->map_img.h / ray->perp_wall_dist);
	wall_top->y = -line_height + vars->img.h / 2;
	end = *wall_top;
	end.y = line_height + (vars->img.h / 2);
	while (i < PIX_PER_RAY)
	{
		print_display_from_ray(wall_top, &end, vars, ray);
		i++;
		wall_top->x++;
	}
	wall_top->x -= PIX_PER_RAY;
}

void put_img_to_img(t_data *src, t_data *dst)
{
	int		x;
	int		y;
	t_color	pixel;

	y = -1;
	while (++y < dst->h)
	{
		x = -1;
		while (++x < dst->w)
		{
			pixel.x = get_pixel_img(src, x * ((float)src->w / dst->w), y * ((float)src->h / dst->h));
			if (pixel.r+pixel.g+pixel.b != 0)
				my_mlx_pixel_put(dst, x, y, pixel.x);
		}
	}
}

int	raycast(t_mlx *vars)
{
	t_pos	wall_top;

	ft_bzero(&vars->ray, sizeof(vars->ray));
	wall_top = get_carac_pos(vars->map, &vars->offset);
	vars->ray.map_pos = get_carac_index(vars->map);
	vars->ray.pos_x = vars->ray.map_pos.x \
	+ ((double)vars->offset.x / TILE_SIZE);
	vars->ray.pos_y = vars->ray.map_pos.y \
	+ ((double)vars->offset.y / TILE_SIZE);
	vars->ray.initial_pos = vars->ray.map_pos;
	wall_top.x = 0;
	while (wall_top.x < vars->img.w)
	{
		init_value_for_cast(&vars->ray, vars, &wall_top);
		side_dist_and_stepper(&vars->ray);
		one_cast(&vars->ray, vars);
		wall_printer_from_cast(&vars->ray, vars, &wall_top);
		wall_top.x += PIX_PER_RAY;
	}
	put_img_to_img(&vars->overlay, &vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	print_ray_param(&vars->ray);
	vars->fps++;
	return (0);
}
