/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:41:54 by sjean             #+#    #+#             */
/*   Updated: 2024/11/02 12:04:31 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"
#include "../headers/cube3d.h"

int	get_arg(char *argv, t_info *info)
{
	char	*line_key;
	int		key;

	info->map_fd = open(argv, O_RDONLY);
	if (info->map_fd == -1)
		return (E_CANT_OPEN);
	line_key = get_next_line(info->map_fd);
	while (line_key)
	{
		key = key_finder(line_key);
		if (key == -1)
			return (free(line_key), E_NO_MORE_KEY);
		else if (key != KEY_C && key != KEY_F)
		{
			if (get_key_value(line_key, key, info) == E_NO_MORE_KEY)
				return (free(line_key), E_NO_MORE_KEY);
		}
		else if (get_color(line_key, key, info) == E_WRONG_COLOR)
			return (E_WRONG_COLOR);
		free (line_key);
		line_key = get_next_line(info->map_fd);
	}
	return (SUCCESS);
}

t_info	*init_info(void)
{
	int		i;
	t_info	*info;

	i = -1;
	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	ft_memset(info, 0, sizeof(t_info));
	while (++i < 3)
	{
		info->ceiling[i] = -1;
		info->floor[i] = -1;
	}
	return (info);
}

int	check_format(char *map, char *find)
{
	char	*var;

	var = ft_strnstr(map, find, ft_strlen(map));
	if (ft_strlen(map) > ft_strlen(find) && var && \
	ft_strlen(var) == ft_strlen(find))
		return (SUCCESS);
	else
		return (E_FORMAT);
}

int	parsing_cube(char *arg, t_info **info)
{
	// t_info	*info;
	int		result;

	// info = init_info();
	// if (!info)
	// 	return (error_msg(E_MALLOC), 0);
	if (check_format(arg, ".cub") == E_FORMAT)
		return (error_msg(E_FORMAT), 0);
	result = get_arg(arg, *info);
	if (result == E_NO_MORE_KEY)
	{
		if (!valid_key(*info))
			return (error_msg(E_WRONG_KEY), free(*info), 0);
		else
			if (get_map(*info) != SUCCESS)
				return (error_msg(E_INVALID_MAP), \
				freetab((*info)->map), free(*info), 0);
	}
	else if (result == E_WRONG_COLOR)
		return (error_msg(E_WRONG_COLOR), free(*info), 0);
	else if (result == E_CANT_OPEN)
		return (error_msg(E_CANT_OPEN), free(*info), 0);
	if (init_data_texture(*info) == E_MALLOC)
		return (free(*info), 0);
	return (SUCCESS);
}
