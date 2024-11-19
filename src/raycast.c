/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/19 16:06:52 by lrichaud         ###   ########lyon.fr   */
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

int	print_wall_from_ray(t_pos *origin, t_pos *end, t_data *img, int color)
{
	t_pos	current;

	current.x = origin->x;
	current.y = 0;
	while (current.y < origin->y)
	{
		my_mlx_pixel_put(img, current.x, current.y, 0xFF000030);
		current.y++;
	}
	while (current.y < end->y)
	{
		my_mlx_pixel_put(img, current.x, current.y, color);
		current.y++;
	}
	while (current.y < img->h)
	{
		my_mlx_pixel_put(img, current.x, current.y, 0xFF170501);
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
	int		color;
	t_pos	end;
	int		i;

	i = 0;
	line_height = (int)(vars->map_img.h / ray->perp_wall_dist);
	origin->y = -line_height + vars->img.h / 2;
	if (origin->y < 0)
		origin->y = 0;
	end = *origin;
	end.y = line_height + (vars->img.h / 2);
	if (end.y >= vars->img.h)
		end.y = vars->img.h - 1;
	if (ray->side == 1)
		color = 0xFFA9846A;
	else
		color = 0xFF654321;
	while (i < PIX_PER_RAY)
	{
		print_wall_from_ray(origin, &end, &vars->img, color);
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
