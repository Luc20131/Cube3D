/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/07 20:43:18 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#define PIX_PER_RAY 1

void	side_dist_and_stepper(t_ray	*ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->w_step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->w_step.x = 1;
		ray->side_dist.x = (ray->map_pos.x + 1.0 - ray->pos.x) \
		* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->w_step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->w_step.y = 1;
		ray->side_dist.y = (ray->map_pos.y + 1.0 - ray->pos.y) \
		* ray->delta_dist.y;
	}
}

int	print_texture_from_ray(t_pos *wall_top, t_pos *end, t_mlx *vars)
{
	t_pos	current;
	t_data	img_wall;

	current.x = wall_top->x;
	current.y = 0;
	if (current.y >= wall_top->y)
		current.y = wall_top->y;
	img_wall = select_texture(vars->stats->img_texture, vars);
	print_ceilling(&current, vars, wall_top);
	print_wall(&current, vars, end, &img_wall);
	print_floor(&current, vars);
	return (0);
}

void	stop_casting(t_ray *ray, char **map, t_pos size_map)
{
	if (ray->map_pos.x < 0 || ray->map_pos.y < 0 \
			|| ray->map_pos.x >= size_map.x \
			|| ray->map_pos.y >= size_map.y)
	{
		ray->side_dist.x = ray->delta_dist.x + 1;
		ray->side_dist.y = ray->delta_dist.y + 1;
		ray->hit = 1;
	}
	else if (map[ray->map_pos.y][ray->map_pos.x] > '0')
		ray->hit = 1;
}

int	one_cast(t_ray *ray, t_mlx *vars)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->w_step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->w_step.y;
			ray->side = 1;
		}
		stop_casting(ray, vars->map, vars->size_map);
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
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
	line_height = (int)(vars->layer[LAYER_RAYCAST].h / ray->perp_wall_dist);
	wall_top->y = -line_height + (vars->layer[LAYER_RAYCAST].h >> 1);
	end = *wall_top;
	end.y = line_height + (vars->layer[LAYER_RAYCAST].h >> 1);
	while (i < PIX_PER_RAY)
	{
		print_texture_from_ray(wall_top, &end, vars);
		i++;
		wall_top->x++;
	}
	wall_top->x -= PIX_PER_RAY;
}

void	raycast(t_mlx *vars)
{
	t_pos	origin;

	origin = vars->player_data.pixel_pos;
	vars->ray.pos.x = vars->player_data.float_pos.x;
	vars->ray.pos.y = vars->player_data.float_pos.y;
	vars->ray.map_pos.x = (int) vars->player_data.float_pos.x;
	vars->ray.map_pos.y = (int) vars->player_data.float_pos.y;
	vars->ray.initial_pos = vars->ray.map_pos;
	origin.x = 0;
	if (vars->player_data.movement.rotating == 1)
		rotate_left(vars);
	else if (vars->player_data.movement.rotating == -1)
		rotate_right(vars);
	while (origin.x < vars->layer[LAYER_RAYCAST].w)
	{
		init_value_for_cast(&vars->ray, vars, &origin);
		side_dist_and_stepper(&vars->ray);
		one_cast(&vars->ray, vars);
		wall_printer_from_cast(&vars->ray, vars, &origin);
		origin.x += PIX_PER_RAY;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, \
		vars->layer[LAYER_RAYCAST].img, 0, 0);
}
