/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:31:17 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:45:48 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top)
{
	t_color	pixel;

	while (current->y < wall_top->y)
	{
		pixel.r = vars->stats->ceiling[0];
		pixel.g = vars->stats->ceiling[1];
		pixel.b = vars->stats->ceiling[2];
		((int *)vars->layer[RAYCAST].addr)[current->y * \
		(vars->layer[RAYCAST].line_length >> 2) + current->x] = pixel.x;
		current->y++;
	}
	return (0);
}

int	print_floor(t_pos *current, t_mlx *vars)
{
	t_color	pixel;

	while (current->y < vars->layer[RAYCAST].h)
	{
		pixel.r = vars->stats->floor[0];
		pixel.g = vars->stats->floor[1];
		pixel.b = vars->stats->floor[2];
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
	const int	line_length = (vars->layer[RAYCAST].line_length >> 2);
	const float	step = ((float)img->h / (end->y - current->y));

	tex.x = init_pixel_tex_x(&vars->ray, vars) * img->pixels;
	tex.y = init_pixel_tex_y(current, step);
	while ((current->y < end->y) & (current->y < vars->layer[RAYCAST].h))
	{
		tex.y += step;
		pixel.x = *(unsigned int *)((img->addr + (int)tex.y * \
			img->line_length) + ((int)tex.x));
		((int *)vars->layer[RAYCAST].addr)[current->y * \
			line_length + current->x] = pixel.x;
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
