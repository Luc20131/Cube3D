/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2024/12/13 14:38:27 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top)
{
	t_color	pixel;

	while (current->y < wall_top->y)
	{
		pixel.x = SKY_COLOR;
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_floor(t_pos *current, t_mlx *vars)
{
	t_color	pixel;

	while (current->y < vars->layer[LAYER_RAYCAST].h)
	{
		pixel.x = GROUND_COLOR;
		((int *)vars->layer[LAYER_RAYCAST].addr)[current->y * \
		(vars->layer[LAYER_RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_wall(t_pos *current, t_mlx *vars, t_pos *end, t_data *img)
{
	t_posf		tex;
	t_color		pixel;
	const int	line_length = (vars->layer[LAYER_RAYCAST].line_length >> 2);
	const float	step = ((float)img->h / (end->y - current->y));

	tex.x = init_pixel_tex_x(&vars->ray, vars) * img->pixels;
	tex.y = init_pixel_tex_y(current, step);
	while ((current->y < end->y) & (current->y < vars->layer[LAYER_RAYCAST].h))
	{
		tex.y += step;
		pixel.x = *(unsigned int *)((img->addr + (int)tex.y * \
			img->line_length) + ((int)tex.x));
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

t_data	img_cut(t_pos pos, t_mlx *vars, t_pos pos_)
{
	t_sprite_slice	slice;
	int				j;
	int				i;

	slice = (t_sprite_slice){pos.y * TILE_SIZE, pos.x * TILE_SIZE,\
	 TILE_SIZE, TILE_SIZE};
	i = -1;
	while (++i < slice.width)
	{
		j = -1;
		while (++j < slice.height)
		{
			put_pixel_img(&vars->layer[LAYER_MAP], pos_.x + j, pos_.y + i, \
		get_pixel_img(&vars->layer[LAYER_ACHANGER], slice.x + j, slice.y + i));
		}
	}
	return (vars->layer[LAYER_ACHANGER]);
}
