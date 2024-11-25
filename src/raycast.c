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
#define ROT_SPEED 0.05
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
	line_height = (int)(vars->img.h / ray->perp_wall_dist);
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

void    upscale_raycast_to_screen(t_mlx *vars, t_data *screen)
{
	t_pos    screen_pos;
	t_pos    raycast_pos;
	unsigned int    pixel_color[WIDTH];
	char    *dst;
	int        nb_pixels;
	int        nb_lines;
	int        nb_pixel_in_lines;
	float    ratio_w;
	float    ratio_h;
	int        i;

	ratio_h = HEIGHT_WIN / HEIGHT;
	ratio_w = WIDTH_WIN / WIDTH;
	screen_pos.x = 0;
	screen_pos.y = 0;
	nb_pixels = screen->bits_per_pixel >> 3;
	raycast_pos = screen_pos;
	while (raycast_pos.y < vars->img.h)
	{
		screen_pos.x = 0;
		raycast_pos.x = 0;
		nb_lines = screen_pos.y * screen->line_length;
		int nb_lines_raycast = raycast_pos.y * vars->img.line_length;
		while (raycast_pos.x < vars->img.w)
		{
			nb_pixel_in_lines = screen_pos.x * nb_pixels;
			dst = screen->addr + (nb_lines + nb_pixel_in_lines);
			pixel_color[raycast_pos.x] = *(unsigned int *)((vars->img.addr + (nb_lines_raycast) + (raycast_pos.x * nb_pixels)));
			i = 0;
			while (i < ratio_w)
			{
				*(unsigned int *) dst = pixel_color[raycast_pos.x];
				dst += nb_pixels;
				i++;
			}
			raycast_pos.x++;
			screen_pos.x += ratio_w;
		}
		i = 0;
		while (i < ratio_h)
		{
			screen_pos.x = 0;
			raycast_pos.x = 0;
			nb_lines = screen_pos.y * screen->line_length;
			while (raycast_pos.x < vars->img.w)
			{
				nb_pixel_in_lines = screen_pos.x * nb_pixels;
				dst = screen->addr + (nb_lines + nb_pixel_in_lines);
				int j = 0;
				while (j < ratio_w)
				{
					*(unsigned int *) dst = pixel_color[raycast_pos.x];
					dst += nb_pixels;
					j++;
				}
				raycast_pos.x++;
				screen_pos.x += ratio_w;
			}
			screen_pos.y++;
			i++;
		}
		raycast_pos.y++;
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
      if (vars->movement.rotating == 1)
      {
        double oldDirX = ray->dir_x;
      	ray->dir_x = ray->dir_x * cos(-ROT_SPEED) - ray->dir_y * sin(-ROT_SPEED);
      	ray->dir_y = oldDirX * sin(-ROT_SPEED) + ray->dir_y * cos(-ROT_SPEED);
      	double oldPlaneX = ray->plane_x;
      	ray->plane_x = ray->plane_x * cos(-ROT_SPEED) - ray->plane_y * sin(-ROT_SPEED);
      	ray->plane_y = oldPlaneX * sin(-ROT_SPEED) + ray->plane_y * cos(-ROT_SPEED);
      }
    else if (vars->movement.rotating == -1)
       {
        double oldDirX = ray->dir_x;
      	ray->dir_x = ray->dir_x * cos(ROT_SPEED) - ray->dir_y * sin(ROT_SPEED);
      	ray->dir_y = oldDirX * sin(ROT_SPEED) + ray->dir_y * cos(ROT_SPEED);
      	double oldPlaneX = ray->plane_x;
      	ray->plane_x = ray->plane_x * cos(ROT_SPEED) - ray->plane_y * sin(ROT_SPEED);
      	ray->plane_y = oldPlaneX * sin(ROT_SPEED) + ray->plane_y * cos(ROT_SPEED);
       }
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
	upscale_raycast_to_screen(vars, &vars->screen);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->screen.img, 0, 0);
	vars->fps++;
	return (0);
}
