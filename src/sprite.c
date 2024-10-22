/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/10/21 08:04:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <math.h>
#include <stdio.h>

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

t_data	new_img_from_file(char *path, t_mlx *vars)
{
	t_data	tile;

	tile.img = mlx_xpm_file_to_image(vars->mlx, path, &tile.w, &tile.h);
	if (!tile.img)
	{
		tile.addr = NULL;
		return (tile);
	}
	tile.addr = mlx_get_data_addr(tile.img, &tile.bits_per_pixel, \
		&tile.line_length, &tile.endian);
	return (tile);
}

t_data	resize_img(t_mlx *vars, t_data *img, unsigned int width, unsigned int height)
{
	t_pos			pos_resized;
	t_pos			pos_img;
	t_data			resized_img;
	int				color;
	// int				next_color;
	// int				delta_color;
	t_pos			ratio;
	int				i;
	int				j;

	ratio.x = (width / img->w);
	ratio.y = (height / img->h);
	resized_img = new_img(vars, width, height);
	pos_img.y = 0;
	pos_resized.y = 0;
	while (pos_img.y < img->h)
	{
		pos_img.x = 0;
		pos_resized.x = 0;
		while (pos_img.x < img->w)
		{
			color = get_pixel_img(img, pos_img.x, pos_img.y);
			// my_mlx_pixel_put(&resized_img, pos_resized.x, pos_resized.y, color);

			// if (pos_img.x + 1 < img->w)
			// {
			// 	next_color = get_pixel_img(img, pos_img.x + 1, pos_img.y);
			// 	delta_color = next_color - color;
				i = 0;
				while (i < ratio.x)
				{
					// color += delta_color;
					// color = get_pixel_img(img, pos_img.x, pos_img.y);
					j = 0;
					while (j != pos_img.x && j != pos_img.y)
					{
						my_mlx_pixel_put(&resized_img, pos_resized.x, pos_resized.y, color);
						my_mlx_pixel_put(&resized_img, pos_resized.x, pos_resized.y + i, color);
						my_mlx_pixel_put(&resized_img, pos_resized.x, pos_resized.y + j, color);
						my_mlx_pixel_put(&resized_img, pos_resized.x + i, pos_resized.y, color);
						my_mlx_pixel_put(&resized_img, pos_resized.x + j, pos_resized.y, color);
						my_mlx_pixel_put(&resized_img, pos_resized.x + i, pos_resized.y + j, color);
						my_mlx_pixel_put(&resized_img, pos_resized.x + j, pos_resized.y + i, color);
						j++;
					}
					i++;
				}
			// }
			// my_mlx_pixel_put(&resized_img, pos_resized.x + 1, pos_resized.y, color);
			// my_mlx_pixel_put(&resized_img, pos_resized.x, pos_resized.y + 1, color);
			// my_mlx_pixel_put(&resized_img, pos_resized.x + 1, pos_resized.y + 1, color);
			pos_resized.x += ratio.x;
			pos_img.x++;
		}
		pos_resized.y += ratio.y;
		pos_img.y++;
	}
	mlx_destroy_image(vars->mlx, img->img);
	return (resized_img);
}
