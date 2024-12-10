/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 02:06:05 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/07 00:28:50 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "cube3d.h"

void	init_value_for_cast(t_ray *ray, t_mlx *vars, t_pos *origin)
{
	ray->hit = 0;
	ray->map_pos = ray->initial_pos;
	ray->camera_x = ((2 * origin->x) / (float) \
		vars->layer[LAYER_RAYCAST].w) - 1;
	ray->ray_dir.x = ray->dir.x + ray->plane.x * ray->camera_x;
	ray->ray_dir.y = ray->dir.y + ray->plane.y * ray->camera_x;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = __FLT_MAX__;
	else
		ray->delta_dist.x = fabs(1.f / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = __FLT_MAX__;
	else
		ray->delta_dist.y = fabs(1.f / ray->ray_dir.y);
}

void	print_ray_param(t_ray *ray)
{
	printf("\x1B[H\x1B[Jdir_x : %lf\ndir_y : %lf\ndeltadir_x : %lf\n" \
		"deltadir_y : %lf\n" \
		"step_x : %lf\nstep_y : %lf\nside_dist_x : %lf\nsize_dist_y : %lf\n" \
		"pos_x : %lf\npos_y : %lf\n" \
		"plane.x : %lf\nplane_y : %lf\nray_dir_x : %lf\nray_dir_y : %lf\n" \
		"hit : %d\nside : %d\nmap_pos:\n\t-x : %d\n\t-y : %d\ncamera_x : %lf\n" \
		"perp_wall_dist : %lf\nend_ray.x : %d\nend_ray.y : %d\n",
		ray->dir.x, ray->dir.y, ray->delta_dist.x, ray->delta_dist.y, \
		ray->w_step.x, ray->w_step.y, ray->side_dist.x, ray->side_dist.y, \
		ray->pos.x, ray->pos.y, ray->plane.x, ray->plane.y, ray->ray_dir.x, \
		ray->ray_dir.y, ray->hit, ray->side, ray->map_pos.x, ray->map_pos.y, \
		ray->camera_x, ray->perp_wall_dist, ray->end_ray.x, ray->end_ray.y);
}
