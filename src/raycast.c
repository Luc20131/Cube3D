/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/20 16:54:48 by sjean            ###   ########.fr       */
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

int	print_wall_from_ray(t_pos *origin, t_pos *end, t_mlx *vars, t_ray *ray)
{
	t_pos	current;
	double	wallx;
	double	step;
	double	tex_pos;
	int		texx;
	int		texy;
	int 	pixel;

	current.x = origin->x;
	if (current.x < 0)
		current.x = 0;
	current.y = 0;
	if (current.y >= origin->y)
		current.y = origin->y;
	step = 1.0 * vars->stats->img_texture[0].h / (end->y - origin->y);
	tex_pos = (origin->y - vars->img.h / 2 + (end->y - origin->y) / 2) * step;
	
	if (ray->side == 0)
		wallx = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wallx = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wallx -= floor(wallx);

	texx = (int)(wallx * (double)(vars->stats->img_texture[0].w));
	if (ray->side == 0 && ray->dir_x > 0)
		texx = vars->stats->img_texture[0].w - texx - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		texx = vars->stats->img_texture[0].w - texx - 1;
	
	while (current.y < origin->y)
	{
		my_mlx_pixel_put(&vars->img, current.x, current.y, 0xFF000030);
		current.y++;
	}
	while (current.y < end->y && current.y < vars->img.h)
	{
		texy = (int)tex_pos & (vars->stats->img_texture[0].h - 1);	
		if (current.y < 0)
		{
			tex_pos += (step * (-1 * current.y));
			current.y = 0;	
		}
		else
			tex_pos += step;
		
		pixel = get_pixel_img(&vars->stats->img_texture[0], texx, texy);
		if (ray->side == 1)
			pixel = (pixel >> 1) & 8355711;
		my_mlx_pixel_put(&vars->img, current.x, current.y, pixel);
		current.y++;
	}
	while (current.y < vars->img.h)
	{
		my_mlx_pixel_put(&vars->img, current.x, current.y, 0xFF170501);
		current.y++;
	}
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

void	wall_printer_from_cast(t_ray *ray, t_mlx *vars, t_pos *origin)
{
	int		line_height;
	t_pos	end;
	int		i;

	i = 0;
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.001;
	line_height = (int)(vars->map_img.h / ray->perp_wall_dist);
	origin->y = -line_height + vars->img.h / 2;
	// if (origin->y < 0)
	// 	origin->y = 0;
	end = *origin;
	end.y = line_height + (vars->img.h / 2);
	// if (end.y >= vars->img.h)
	// 	end.y = vars->img.h - 1;
	while (i < PIX_PER_RAY)
	{
		print_wall_from_ray(origin, &end, vars, ray);
		i++;
		origin->x++;
	}
	origin->x -= PIX_PER_RAY;
}

int	raycast(t_mlx *vars)
{
	t_ray	ray;
	t_pos	origin;

	ft_bzero(&ray, sizeof(ray));
	origin = get_carac_pos(vars->map, &vars->offset);
	ray.map_pos = get_carac_index(vars->map);
	ray.pos_x = ray.map_pos.x + ((double)vars->offset.x / TILE_SIZE);
	ray.pos_y = ray.map_pos.y + ((double)vars->offset.y / TILE_SIZE);
	ray.initial_pos = ray.map_pos;
	origin.x = 0;
	while (origin.x < vars->img.w)
	{
		init_value_for_cast(&ray, vars, &origin);
		side_dist_and_stepper(&ray);
		one_cast(&ray, vars);
		wall_printer_from_cast(&ray, vars, &origin);
		origin.x += PIX_PER_RAY;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	print_ray_param(&ray);
	vars->fps++;
	return (0);
}
