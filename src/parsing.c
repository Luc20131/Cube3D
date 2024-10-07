/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:41:54 by sjean             #+#    #+#             */
/*   Updated: 2024/10/02 17:31:43 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"
#include "../headers/cube3d.h"

//read file and get the keys for texture and color =============================
int	get_arg(char *argv, t_info *info)
{
	char	*line_key;
	int		key;

	info->map_fd = open(argv, O_RDONLY);
	if (info->map_fd == -1)
		return (1);
	line_key = get_next_line(info->map_fd);
	while (line_key)
	{
		key = key_finder(line_key); 
		if (key == -1)
			return (1);
		else if (key != KEY_C && key != KEY_F)
		{
			if (get_key_value(line_key, key, info) == E_MALLOC)
				return (1);
		}
		else
			if (get_color(line_key, key, info) == E_WRONG_COLOR)
				return (1);
		free (line_key);
		line_key = get_next_line(info->map_fd);
	}
	return (0);
}

int parsing_cube(char *arg)
{
	t_info *info;

	info = ft_calloc(1, sizeof(t_info));
	ft_memset(info, 0, sizeof(t_info));
	if (get_arg(arg, info) == 1)
		return (1);
	return (0);
}
