/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/05 18:48:22 by sjean            ###   ########.fr       */
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
	float	step;
	t_data	img_wall;

	(void)ray;
	current.x = wall_top->x;
	current.y = 0;
	if (current.y >= wall_top->y)
		current.y = wall_top->y;
	img_wall = select_texture(vars->stats->img_texture, vars);
	step = (1.0 * img_wall.h / (end->y - wall_top->y));
	current.y = wall_top->y;
	print_wall(&current, vars, step, end);
	vertical_raycast(vars, end);
	return (0);
}
/*
	print_ceilling(&current, vars, wall_top);
	print_floor(&current, vars, ray);
*/ 

int	one_cast(t_ray *ray, t_mlx *vars)
{
	t_pos	map_len;
	int		len;

	map_len = size_map(vars->map);
	len = -1;
	while (ray->hit == 0 && ++len != 30)
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
		if (ray->map_pos.y < map_len.y && ray->map_pos.x < map_len.x && ray->map_pos.y >= 0 && ray->map_pos.x >= 0)
			if (vars->map[ray->map_pos.y][ray->map_pos.x] > '0')
				ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
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
		print_display_from_ray(wall_top, &end, vars, ray);
		i++;
		wall_top->x++;
	}
	wall_top->x -= PIX_PER_RAY;
}

void	put_img_to_img(t_data *src, t_data *dst)
{
	int		x;
	int		y;
	t_posf	ratio;
	t_color	pixel;

	ratio.x = (float)src->w / dst->w;
	ratio.y = (float)src->h / dst->h;
	y = -1;
	while (++y < dst->h)
	{
		x = -1;
		while (++x < dst->w)
		{
			pixel.x = get_pixel_img(src, x * ratio.x, y * ratio.y);
			if (pixel.r+pixel.g+pixel.b != 0)
				((int *)dst->addr)[y * (dst->line_length >> 2) + x] = pixel.x;
		}
	}
}

int	raycast(t_mlx *vars)
{
	t_pos	origin;

	origin = vars->player_data.pixel_pos;
	vars->ray.pos_x = vars->player_data.float_pos.x;
	vars->ray.pos_y = vars->player_data.float_pos.y;
	vars->ray.map_pos.x = (int) vars->player_data.float_pos.x;
	vars->ray.map_pos.y = (int) vars->player_data.float_pos.y;
	vars->ray.initial_pos = vars->ray.map_pos;
	origin.x = 0;
	if (vars->player_data.movement.rotating == 1)
	{
		float oldDirX = vars->ray.dir_x;
		vars->ray.dir_x = vars->ray.dir_x * cos(-ROT_SPEED) - vars->ray.dir_y * sin(-ROT_SPEED);
		vars->ray.dir_y = oldDirX * sin(-ROT_SPEED) + vars->ray.dir_y * cos(-ROT_SPEED);
		float oldPlaneX = vars->ray.plane_x;
		vars->ray.plane_x = vars->ray.plane_x * cos(-ROT_SPEED) - vars->ray.plane_y * sin(-ROT_SPEED);
		vars->ray.plane_y = oldPlaneX * sin(-ROT_SPEED) + vars->ray.plane_y * cos(-ROT_SPEED);
	}
	else if (vars->player_data.movement.rotating == -1)
	{
		float oldDirX = vars->ray.dir_x;
		vars->ray.dir_x = vars->ray.dir_x * cos(ROT_SPEED) - vars->ray.dir_y * sin(ROT_SPEED);
		vars->ray.dir_y = oldDirX * sin(ROT_SPEED) + vars->ray.dir_y * cos(ROT_SPEED);
		float oldPlaneX = vars->ray.plane_x;
		vars->ray.plane_x = vars->ray.plane_x * cos(ROT_SPEED) - vars->ray.plane_y * sin(ROT_SPEED);
		vars->ray.plane_y = oldPlaneX * sin(ROT_SPEED) + vars->ray.plane_y * cos(ROT_SPEED);
	}
	while (origin.x < vars->layer[LAYER_RAYCAST].w)
	{
		init_value_for_cast(&vars->ray, vars, &origin);
		side_dist_and_stepper(&vars->ray);
		one_cast(&vars->ray, vars);
		wall_printer_from_cast(&vars->ray, vars, &origin);
		origin.x += PIX_PER_RAY;
	}
	put_img_to_img(&vars->layer[LAYER_OVERLAY], &vars->layer[LAYER_RAYCAST]);
	upscale_rc_to_screen(vars, &vars->layer[LAYER_SCREEN]);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->layer[LAYER_SCREEN].img, 0, 0);
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->layer[LAYER_RAYCAST].img, 0, 0);
	// print_ray_param(&vars->ray);
	vars->fps++;
	return (0);
}
