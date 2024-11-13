/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/13 02:02:54 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	camera_x;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	ray_dir_x;
	double	ray_dir_y;
	int		hit;
	t_pos	map_pos;
	double	perp_wall_dist;
	int		side;
	t_pos	end_ray;
} t_ray;

void	print_ray_param(t_ray *ray)
{
	printf("\x1B[H\x1B[Jdir_x : %lf\ndir_y : %lf\ndeltadir_x : %lf\ndeltadir_y : %lf\n"
		"step_x : %lf\nstep_y : %lf\nside_dist_x : %lf\nsizeDistY : %lf\npos_x : %lf\npos_y : %lf\n" \
		"plane_x : %lf\nplane_y : %lf\nray_dir_x : %lf\nray_dir_y : %lf\nhit : %d\nside : %d\n" \
		"map_pos:\n\t-x : %d\n\t-y : %d\ncamera_x : %lf\nperp_wall_dist : %lf\nend_ray.x : %d\nend_ray.y : %d\n"
		,ray->dir_x, ray->dir_y, ray->delta_dist_x, ray->delta_dist_y, ray->step_x \
		, ray->step_y, ray->side_dist_x, ray->side_dist_y, ray->pos_x, ray->pos_y \
		, ray->plane_x, ray->plane_y, ray->ray_dir_x, ray->ray_dir_y, ray->hit
		, ray->side, ray->map_pos.x, ray->map_pos.y, ray->camera_x, ray->perp_wall_dist, ray->end_ray.x, ray->end_ray.y);
}

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
		ray->side_dist_x = (ray->map_pos.x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_pos.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_pos.y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

int	print_wall_from_ray(t_pos *origin, t_pos *end, t_data *img, int	color)
{
	t_pos	current;

	current.x = origin->x;
	current.y = 0;
	while (current.y < origin->y)
	{
		my_mlx_pixel_put(img, current.x, current.y, 0xFF001000);
		current.y++;
	}
	while (current.y < end->y)
	{
		my_mlx_pixel_put(img, current.x, current.y, color);
		current.y++;
	}
	while (current.y < img->h)
	{
		my_mlx_pixel_put(img, current.x, current.y, 0xFFFF0000);
		current.y++;
	}
	return (0);
};

int	one_cast(t_ray *ray, t_mlx *vars)
{
	// ray->delta_dist_x = sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y) / (ray->ray_dir_x * ray->ray_dir_x));
	// ray->delta_dist_y = sqrt(1 + (ray->ray_dir_x * ray->ray_dir_x) / (ray->ray_dir_y * ray->ray_dir_y));
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
	ray->end_ray.x = ray->side_dist_x;
	ray->end_ray.y = ray->side_dist_y;
	if(ray->side == 0)
		ray->perp_wall_dist = (ray->map_pos.x * TILE_SIZE - ray->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist =  (ray->map_pos.y * TILE_SIZE- ray->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	// ray->perp_wall_dist *= cos(ray->camera_x * 0.66);
	// print_ray_param(ray);
	// my_draw_line(get_carac_pos(vars->map, &vars->offset), (t_pos) {ray->pos_x + (ray->end_ray.x ), ray->pos_y + (ray->end_ray.y )}, &vars->mini_map);
	return (0);
}

int	raycast(t_mlx *vars)
{
	t_data	img;
	t_ray	ray;
	t_pos	origin;
	t_pos	initial_pos;
	int		color;

	img = vars->img;
	origin = get_carac_pos(vars->map, &vars->offset);
	ray.map_pos = get_carac_index(vars->map);
	ray.pos_x = ray.map_pos.x + ((double)vars->offset.x / TILE_SIZE);
	ray.pos_y = ray.map_pos.y + ((double)vars->offset.y / TILE_SIZE);
	initial_pos = ray.map_pos;
	origin.x = 0;
	while (origin.x < vars->img.w)
	{
		ray.plane_x = 0;
		ray.plane_y = 0.66;
		ray.dir_x = -0.2;
		ray.dir_y = -0.2;
		ray.side_dist_x = 0;
		ray.side_dist_y = 0;
		ray.step_x = 0;
		ray.step_y = 0;
		color = 0xFFFF00FF;
		ray.map_pos = initial_pos;
		ray.hit = 0;
		ray.camera_x = (2 * origin.x) / (double)vars->img.w - 1;
		ray.ray_dir_x = ray.dir_x + ray.plane_x * ray.camera_x;
		ray.ray_dir_y = ray.dir_y + ray.plane_y * ray.camera_x;
		if (ray.ray_dir_x == 0)
			ray.delta_dist_x = 1e30;
		else
			ray.delta_dist_x = fabs(1/ray.ray_dir_x);
		if (ray.ray_dir_y == 0)
			ray.delta_dist_y = 1e30;
		else
			ray.delta_dist_y = fabs(1/ray.ray_dir_y);
		side_dist_and_stepper(&ray);
		one_cast(&ray, vars);
		int lineHeight = (int)(vars->map_img.h / ray.perp_wall_dist);
		// print_ray_param(&ray);
		t_pos	end;

		origin.y = -lineHeight + img.h / 2;
		if (origin.y < 0)
			origin.y = 0;
		end = origin;
		end.y = lineHeight + (img.h / 2);
		if(end.y >= img.h)
			end.y = img.h - 1;
		if (ray.side == 1)
			color /= 2;
		print_wall_from_ray(&origin, &end, &img, color);
		origin.x++;
		// usleep(500000);
	}
	print_ray_param(&ray);
	// img = resize_img(vars, &vars->img, WIDTH,  HEIGHT);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}
