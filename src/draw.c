/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2024/12/05 16:16:45 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top)
{
	t_color	pixel;
	float	coef;
	float	half_height;

	half_height = (vars->layer[LAYER_RAYCAST].h / 2.);
	(void)wall_top;
	while (current->y < wall_top->y)
	{
		pixel.x = 0xFF000030;
		coef = (1 - current->y / half_height);
		get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_floor(t_pos *current, t_mlx *vars, t_ray *ray)
{
	t_color	pixel;
	float	coef;
	float	half_height;

	half_height = (1. / vars->layer[LAYER_RAYCAST].h);
	while (current->y < vars->layer[LAYER_RAYCAST].h)
	{
		pixel.x = 0xFF170501;
		coef = ((current->y - half_height) / half_height);
		if (ray->perp_wall_dist > 1)
			get_darker_color(coef, &pixel);
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

void	flashlight(t_pos pixel_pos, t_color *color)
{
	unsigned int distance_sqrt;
	t_color old_color;

	old_color = *color;
	distance_sqrt = ((unsigned int)(pixel_pos.y - (HEIGHT >> 1)) * ((unsigned int)(pixel_pos.y - (HEIGHT >> 1))) \
		+ (((unsigned int)(pixel_pos.x - (WIDTH >> 1)))) * ((unsigned int)(pixel_pos.x - (WIDTH >> 1))));
	if (distance_sqrt < 200000)
	{
		if (distance_sqrt > 130000)
		{
			color->r += (color->r * (200000. - distance_sqrt) / 50000);
			color->g += (color->g * (200000. - distance_sqrt) / 50000);
			color->b += (color->b * (200000. - distance_sqrt) / 50000);
		}
		else
		{
			color->r += (color->r * (200000. - 130000) / 50000);
			color->g += (color->g * (200000. - 130000) / 50000);
			color->b += (color->b * (200000. - 130000) / 50000);
			if (color->r < old_color.r)
				color->r = 255;
			if (color->g < old_color.g)
				color->g = 255;
			if (color->b < old_color.b)
				color->b = 255;
		}
	}
}

int	print_wall(t_pos *current, t_mlx *vars, t_pos *end, t_data *img)
{
	t_posf		tex;
	t_color		pixel;
	const float	inverse_distance = (1. / (vars->ray.perp_wall_dist ));
	const int	line_length = (vars->layer[LAYER_RAYCAST].line_length >> 2);
	const float	step = ((float)img->h / (end->y - current->y));

	tex.x = init_pixel_tex_x(&vars->ray, vars) * img->pixels;
	tex.y = init_pixel_tex_y(current, step);
	while ((current->y < end->y) & (current->y < vars->layer[LAYER_RAYCAST].h))
	{
		tex.y += step;
		if (vars->ray.perp_wall_dist > 13)
			pixel.x = 0x00000000;
		else
		{
			pixel.x = *(unsigned int *)((img->addr + (int)tex.y * \
				img->line_length) + ((int)tex.x));
			if (vars->light)
				flashlight(*current, &pixel);
			if (vars->ray.perp_wall_dist > 0.1)
				get_darker_color(inverse_distance, &pixel);
		}
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
			line_length + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

void	put_pixel_img(t_data *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < img->w && y < img->h)
	{
		*(unsigned int *)(img->addr \
			+ (y * img->line_length + x * img->pixels)) = color;
	}
}

t_data	img_cut(t_pos pos, t_mlx *vars)
{
	t_sprite_slice	slice;
	int				j;
	int				i;

	slice = (t_sprite_slice){pos.y * TILE_SIZE, pos.x * TILE_SIZE, \
		TILE_SIZE, TILE_SIZE};
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			put_pixel_img(&vars->layer[LAYER_MINIMAP], j, i, \
				get_pixel_img(&vars->layer[LAYER_ACHANGER], \
					slice.x + j, slice.y + i));
		}
	}
	return (vars->layer[LAYER_ACHANGER]);
}
