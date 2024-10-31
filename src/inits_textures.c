/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:15:11 by sjean             #+#    #+#             */
/*   Updated: 2024/10/30 23:10:40 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

t_data	new_file_img_info(char *path, t_mlx window)
{
	t_data	image;

	image.img = mlx_xpm_file_to_image(window.mlx, path, &image.w, &image.h);
	if (!image.img)
		return (write(2, "Error\nFile could not be read\n", 29), image);
	else
		image.addr = mlx_get_data_addr(image.img, &(image.bits_per_pixel), \
			&(image.line_length), &(image.endian));
	return (image);
}

int	init_data_texture(t_info *info)
{
	int	i;

	i = -1;
	info->win.mlx = mlx_init();
	while (++i < 4)
	{
		info->img_texture[i] = \
		new_file_img_info(info->texture_path[i], info->win);
		if (info->img_texture[i].img == NULL)
			return (E_MALLOC);
	}
	return (SUCCESS);
}
