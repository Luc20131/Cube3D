/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:15:11 by sjean             #+#    #+#             */
/*   Updated: 2024/11/13 01:49:19 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	init_data_texture(t_info *info, t_mlx *mlx)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		info->img_texture[i] = \
		new_file_img(info->texture_path[i], mlx);
		if (info->img_texture[i].img == NULL)
			return (E_MALLOC);
	}
	return (SUCCESS);
}

t_data	new_file_img(char *path, t_mlx *vars)
{
	t_data	image;

	image.img = mlx_xpm_file_to_image(vars->mlx, path, &image.w, &image.h);
	if (!image.img)
	{
		printf("Error\nImage could not be read\n");
		exit(EXIT_FAILURE);
	}
	image.addr = mlx_get_data_addr(image.img, &(image.bits_per_pixel), \
		&(image.line_length), &(image.endian));
	image.pixels = image.bits_per_pixel >> 3;
	image.bits_per_line = image.line_length >> 2;
	return (image);
}

t_data	new_img(t_mlx *vars, unsigned int width, unsigned int height)
{
	t_data	frame;

	frame.img = mlx_new_image(vars->mlx, width, height);
	if (!frame.img)
		exit_game(vars);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, \
		&frame.line_length, &frame.endian);
	frame.h = height;
	frame.w = width;
	frame.pixels = frame.bits_per_pixel >> 3;
	frame.bits_per_line = frame.line_length >> 2;
	return (frame);
}
