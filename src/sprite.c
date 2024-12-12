/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/15 07:56:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>
#include <stdio.h>

void	my_destroy_img(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

int	create_trgb(const int t, const int r, const int g, const int b)
{
	return (((t & ((1 << 8) - 1))) << 24 | \
		(r & ((1 << 8) - 1)) << 16 | \
		(g & ((1 << 8) - 1)) << 8 | \
		(b & ((1 << 8) - 1)));
}

void	put_img_to_img(t_data *src, t_data *dst)
{
	int		x;
	int		y;
	t_posf	ratio;
	t_color	pixel;

	ratio.x = (float)src->w / dst->w;
	ratio.y = (float)src->h / dst->h;
	y = -1;
	while (++y < dst->h)
	{
		x = -1;
		while (++x < dst->w)
		{
			pixel.x = get_pixel_img(src, x * ratio.x, y * ratio.y);
			if (pixel.r + pixel.g + pixel.b != 0)
				((int *)dst->addr)[y * (dst->line_length >> 2) + x] = pixel.x;
		}
	}
}

int	put_pixel_valid(t_data img, int x, int y)
{
	if (x >= 0 && y >= 0 && x < img.w && y < img.h)
	{
		return (*(unsigned int *)(img.addr + \
		(y * img.line_length + x * img.pixels)) != 0xFF000000 &&
		*(unsigned int *)(img.addr + \
		(y * img.line_length + x * img.pixels)) != 0x00000000);
	}
	return (0);
}

void	put_data_to_img(t_data *dst, t_data src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			if (put_pixel_valid(src, i, j))
			{
				*(unsigned int *)(dst->addr + ((y + j) * dst->line_length \
					+ (x + i) * dst->pixels)) = get_pixel_img(&src, i, j);
			}
			j++;
		}
		i++;
	}
}
