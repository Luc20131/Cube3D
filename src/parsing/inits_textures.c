/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:15:11 by sjean             #+#    #+#             */
/*   Updated: 2024/11/13 00:13:44 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

int	init_data_texture(t_info *info)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		info->img_texture[i] = \
		new_file_img(info->texture_path[i], info->display);
		if (info->img_texture[i].img == NULL)
			return (E_MALLOC);
	}
	return (SUCCESS);
}
