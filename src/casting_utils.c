/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:06:05 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/28 11:40:25 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "cube3d.h"

void	init_value_for_cast(t_ray *ray, t_mlx *vars, t_pos *origin)
{
	ray->hit = 0;
	ray->map_pos = ray->initial_pos;
	ray->camera_x = ((2. * origin->x) / vars->layer[LAYER_RAYCAST].w) - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = INT_MAX;
	else
		ray->delta_dist_x = fabs(1.f / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = INT_MAX;
	else
		ray->delta_dist_y = fabs(1.f / ray->ray_dir_y);
}

void	print_ray_param(t_ray *ray)
{
	printf("\x1B[H\x1B[Jdir_x : %lf\ndir_y : %lf\ndeltadir_x : %lf\n" \
		"deltadir_y : %lf\n" \
		"step_x : %lf\nstep_y : %lf\nside_dist_x : %lf\nsize_dist_y : %lf\n" \
		"pos_x : %lf\npos_y : %lf\n" \
		"plane_x : %lf\nplane_y : %lf\nray_dir_x : %lf\nray_dir_y : %lf\n" \
		"hit : %d\nside : %d\nmap_pos:\n\t-x : %d\n\t-y : %d\ncamera_x : %lf\n" \
		"perp_wall_dist : %lf\nend_ray.x : %d\nend_ray.y : %d\n",
		ray->dir_x, ray->dir_y, ray->delta_dist_x, ray->delta_dist_y, \
		ray->step_x, ray->step_y, ray->side_dist_x, ray->side_dist_y, \
		ray->pos_x, ray->pos_y, ray->plane_x, ray->plane_y, ray->ray_dir_x, \
		ray->ray_dir_y, ray->hit, ray->side, ray->map_pos.x, ray->map_pos.y, \
		ray->camera_x, ray->perp_wall_dist, ray->end_ray.x, ray->end_ray.y);
}
