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
		vars->layer[RAYCAST].w) - 1;
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

int	is_player(const char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

t_pos	tile_selector(t_tile tile[49], int *stats)
{
	int		i;

	i = -1;
	while (++i < 50)
	{
		if (*stats == tile[i].dir)
		{
			return (tile[i].pos);
		}
	}
	return (tile[47].pos);
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
