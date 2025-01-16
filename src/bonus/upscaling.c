/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/16 16:55:05 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/bonus.h"

void	upscaling_first_line(t_data *raycast, t_data *screen, t_upscale *scale)
{
	scale->nb_lines_rc = scale->rc_pos.y * \
		raycast->line_length;
	scale->nb_lines = scale->screen_pos.y * screen->line_length;
	while (scale->rc_pos.x < raycast->w)
	{
		scale->nb_px_in_lines = scale->screen_pos.x * scale->nb_pixels;
		scale->dst = screen->addr + (scale->nb_lines + \
			scale->nb_px_in_lines);
		scale->pixel_color[scale->rc_pos.x] = *(unsigned int *) \
			((raycast->addr + (scale->nb_lines_rc) + \
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

void	upscale_next_lines(t_data *raycast, t_data *screen, t_upscale *scale)
{
	int	j;
	int	i;

	i = -1;
	while (++i < scale->ratio_h)
	{
		scale->screen_pos.x = 0;
		scale->rc_pos.x = -1;
		scale->nb_lines = scale->screen_pos.y * screen->line_length;
		while (++scale->rc_pos.x < raycast->w)
		{
			scale->nb_px_in_lines = scale->screen_pos.x * scale->nb_pixels;
			scale->dst = screen->addr + \
				(scale->nb_lines + scale->nb_px_in_lines);
			j = -1;
			while (++j < scale->ratio_w)
			{
				*(unsigned int *) scale->dst = \
					scale->pixel_color[scale->rc_pos.x];
				scale->dst += scale->nb_pixels;
			}
			scale->screen_pos.x += scale->ratio_w;
		}
		scale->screen_pos.y++;
	}
}

void	upscale_rc_to_screen(t_data *raycast, t_data *screen)
{
	t_upscale	scale;

	scale.ratio_w = (float) screen->w / raycast->w;
	scale.ratio_h = (float) screen->h / raycast->h;
	scale.rc_pos.y = 0;
	scale.rc_pos.x = 0;
	scale.nb_pixels = screen->bits_per_pixel >> 3;
	scale.screen_pos = scale.rc_pos;
	while (scale.rc_pos.y < raycast->h)
	{
		scale.rc_pos.x = 0;
		upscaling_first_line(raycast, screen, &scale);
		upscale_next_lines(raycast, screen, &scale);
		scale.rc_pos.y++;
	}
}
