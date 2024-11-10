/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/09 15:39:46 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct s_ray
{
	double	dirX;
	double	dirY;
	double	cameraX;
	double	deltaDistX;
	double	deltaDistY;
	double	stepX;
	double	stepY;
	double	sideDistX;
	double	sideDistY;
	double	posX;
	double	posY;
	double	planeX;
	double	planeY;
	double	rayDirX;
	double	rayDirY;
	int		hit;
	t_pos	map_pos;
	double	perpWallDist;
	int		side;
	t_pos	end_ray;
} t_ray;

void	print_ray_param(t_ray *ray)
{
	printf("\x1B[H\x1B[JdirX : %lf\ndirY : %lf\ndeltaDirX : %lf\ndeltaDirY : %lf\n"
		"stepX : %lf\nstepY : %lf\nsideDistX : %lf\nsizeDistY : %lf\nposX : %lf\nposY : %lf\n" \
		"planeX : %lf\nplaneY : %lf\nrayDirX : %lf\nrayDirY : %lf\nhit : %d\nside : %d\n" \
		"map_pos:\n\t-x : %d\n\t-y : %d\ncameraX : %lf\nperpWallDist : %lf\nend_ray.x : %d\nend_ray.y : %d\n"
		,ray->dirX, ray->dirY, ray->deltaDistX, ray->deltaDistY, ray->stepX \
		, ray->stepY, ray->sideDistX, ray->sideDistY, ray->posX, ray->posY \
		, ray->planeX, ray->planeY, ray->rayDirX, ray->rayDirY, ray->hit
		, ray->side, ray->map_pos.x, ray->map_pos.y, ray->cameraX, ray->perpWallDist, ray->end_ray.x, ray->end_ray.y);
}

void	side_dist_and_stepper(t_ray	*ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->map_pos.x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->map_pos.x + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->map_pos.y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->map_pos.y + 1.0 - ray->posY) * ray->deltaDistY;
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
	// ray->deltaDistX = sqrt(1 + (ray->rayDirY * ray->rayDirY) / (ray->rayDirX * ray->rayDirX));
	// ray->deltaDistY = sqrt(1 + (ray->rayDirX * ray->rayDirX) / (ray->rayDirY * ray->rayDirY));
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_pos.x += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->map_pos.y += ray->stepY;
			ray->side = 1;
		}
		if (vars->map[ray->map_pos.y][ray->map_pos.x] > '0')
			ray->hit = 1;
	}
	ray->end_ray.x = ray->sideDistX;
	ray->end_ray.y = ray->sideDistY;
	if(ray->side == 0)
		ray->perpWallDist = (ray->map_pos.x * TILE_SIZE - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist =  (ray->map_pos.y * TILE_SIZE- ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
	// ray->perpWallDist *= cos(ray->cameraX * 0.66);
	// print_ray_param(ray);
	my_draw_line(get_carac_pos(vars->map, &vars->offset), (t_pos) {ray->posX + (ray->end_ray.x ), ray->posY + (ray->end_ray.y )}, &vars->mini_map);
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
	ray.posX = ray.map_pos.x + ((double)vars->offset.x / TILE_SIZE);
	ray.posY = ray.map_pos.y + ((double)vars->offset.y / TILE_SIZE);
	initial_pos = ray.map_pos;
	origin.x = 0;
	while (origin.x < vars->img.w)
	{
		ray.planeX = 0;
		ray.planeY = 0.66;
		ray.dirX = -1;
		ray.dirY = 0;
		ray.sideDistX = 0;
		ray.sideDistY = 0;
		ray.stepX = 0;
		ray.stepY = 0;
		color = 0xFFFF00FF;
		ray.map_pos = initial_pos;
		ray.hit = 0;
		ray.cameraX = (2 * origin.x) / (double)vars->img.w - 1;
		ray.rayDirX = ray.dirX + ray.planeX * ray.cameraX;
		ray.rayDirY = ray.dirY + ray.planeY * ray.cameraX;
		if (ray.rayDirX == 0)
			ray.deltaDistX = 1e30;
		else
			ray.deltaDistX = fabs(1/ray.rayDirX);
		if (ray.rayDirY == 0)
			ray.deltaDistY = 1e30;
		else
			ray.deltaDistY = fabs(1/ray.rayDirY);
		side_dist_and_stepper(&ray);
		one_cast(&ray, vars);
		int lineHeight = (int)(vars->map_img.h / ray.perpWallDist);
		// print_ray_param(&ray);
		t_pos	end;

		origin.y = -lineHeight + img.h / 2;
		if (origin.y < 0)
			origin.y = 0;
		end = origin;
		end.y = lineHeight + (img.h / 2);
		if(end.y >= img.h)
			end.y = img.h - 1;
		// print_ray_param(&ray);
		if (ray.side == 1)
			color /= 2;
		print_wall_from_ray(&origin, &end, &img, color);
		origin.x++;
		// usleep(500000);
	}
	// img = resize_img(vars, &vars->img, WIDTH,  HEIGHT);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}
