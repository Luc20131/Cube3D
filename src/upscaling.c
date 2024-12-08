/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>            +#+  +:+       +#+  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/30 16:54:13 by lrichaud            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"

void	upscaling_first_line(t_mlx *vars, t_data *screen, t_upscale *scale)
{
	scale->nb_lines_rc = scale->rc_pos.y * \
		vars->layer[LAYER_RAYCAST].line_length;
	scale->nb_lines = scale->screen_pos.y * screen->line_length;
	while (scale->rc_pos.x < vars->layer[LAYER_RAYCAST].w)
	{
		scale->nb_px_in_lines = scale->screen_pos.x * scale->nb_pixels;
		scale->dst = screen->addr + (scale->nb_lines + \
			scale->nb_px_in_lines);
		scale->pixel_color[scale->rc_pos.x] = *(unsigned int *) \
			((vars->layer[LAYER_RAYCAST].addr + (scale->nb_lines_rc) + \
			(scale->rc_pos.x * scale->nb_pixels)));
		scale->i = 0;
		while (scale->i < scale->ratio_w)
		{
			*(unsigned int *) scale->dst = scale->pixel_color[scale->rc_pos.x];
			scale->dst += scale->nb_pixels;
			scale->i++;
		}
		scale->screen_pos.x += scale->ratio_w;
		scale->rc_pos.x++;
	}
}

void	upscale_next_lines(t_mlx *vars, t_data *screen, t_upscale *scale)
{
	int	j;
	int i;

	i = 0;
	while (i < scale->ratio_h)
	{
		scale->screen_pos.x = 0;
		scale->rc_pos.x = 0;
		scale->nb_lines = scale->screen_pos.y * screen->line_length;
		while (scale->rc_pos.x < vars->layer[LAYER_RAYCAST].w)
		{
			scale->nb_px_in_lines = scale->screen_pos.x * scale->nb_pixels;
			scale->dst = screen->addr + (scale->nb_lines + scale->nb_px_in_lines);
			j = 0;
			while (j < scale->ratio_w)
			{
				*(unsigned int *) scale->dst = scale->pixel_color[scale->rc_pos.x];
				scale->dst += scale->nb_pixels;
				j++;
			}
			scale->rc_pos.x++;
			scale->screen_pos.x += scale->ratio_w;
		}
		scale->screen_pos.y++;
		i++;
	}
}

void	upscale_rc_to_screen(t_mlx *vars, t_data *screen)
{
	t_upscale	scale;

	scale.ratio_w = WIDTH_WIN / WIDTH;
	scale.ratio_h = HEIGHT_WIN / HEIGHT;
	scale.rc_pos.y = 0;
	scale.rc_pos.x = 0;
	scale.nb_pixels = screen->bits_per_pixel >> 3;
	scale.screen_pos = scale.rc_pos;
	while (scale.rc_pos.y < vars->layer[LAYER_RAYCAST].h)
	{
		scale.rc_pos.x = 0;
		upscaling_first_line(vars, screen, &scale);
		upscale_next_lines(vars, screen, &scale);
		scale.rc_pos.y++;
	}
}
