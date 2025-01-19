/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2024/12/05 16:16:45 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "../../headers/types.h"

int	print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top)
{
	t_color	pixel;
	float	coef;
	float	half_height;

	half_height = (vars->layer[RAYCAST].h / 2.);
	(void)wall_top;
	while (current->y < wall_top->y)
	{
		pixel.x = 0xFF000030;
		coef = (1 - current->y / half_height);
		get_darker_color(coef, &pixel);
		((int *)vars->layer[RAYCAST].addr)[current->y * \
		(vars->layer[RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_floor_bonus(t_pos *current, t_mlx *vars, t_ray *ray)
{
	t_color	pixel;
	float	coef;
	float	inverse_heigth;

	inverse_heigth = (1. / vars->layer[RAYCAST].h);
	while (current->y < vars->layer[RAYCAST].h)
	{
		pixel.x = 0xFF170501;
		coef = ((current->y - inverse_heigth) / inverse_heigth);
		if (ray->perp_wall_dist > 1)
			get_darker_color(coef, &pixel);
		((int *)vars->layer[RAYCAST].addr)[current->y * \
		(vars->layer[RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

void	print_wall(t_pos *current, t_mlx *vars, t_pos *end, t_data *img)
{
	t_posf		tex;
	t_color		pixel;
	const float	inverse_distance = (1. / (vars->ray.perp_wall_dist * 2));
	const float	step = ((float)img->h / (end->y - current->y));

	tex.x = init_pixel_tex_x(&vars->ray, vars) * img->pixels;
	tex.y = init_pixel_tex_y(current, step);
	while ((current->y < end->y) & (current->y < vars->layer[RAYCAST].h))
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
			if (vars->ray.perp_wall_dist > 0.5)
				get_darker_color(inverse_distance, &pixel);
		}
		((int *)vars->layer[RAYCAST].addr)[current->y * \
			vars->layer[RAYCAST].bits_per_line + current->x] = pixel.x;
		current->y++;
	}
}

void	put_pixel_img(t_data *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < img->w && y < img->h)
	{
		*(unsigned int *)(img->addr \
			+ (y * img->line_length + x * img->pixels)) = color;
	}
}

t_data	img_cut(t_pos pos, t_mlx *vars, t_pos pos_)
{
	t_sprite_slice	slice;
	int				j;
	int				i;

	slice = (t_sprite_slice){pos.y * TILE_SIZE, pos.x * TILE_SIZE, \
		TILE_SIZE, TILE_SIZE};
	i = -1;
	while (++i < slice.width)
	{
		j = -1;
		while (++j < slice.height)
		{
			put_pixel_img(&vars->layer[MAP], pos_.x + j, pos_.y + i, \
		get_pixel_img(&vars->layer[ACHANGER], slice.x + j, slice.y + i));
		}
	}
	return (vars->layer[ACHANGER]);
}
