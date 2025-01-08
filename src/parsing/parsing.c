/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:41:54 by sjean             #+#    #+#             */
/*   Updated: 2025/01/08 20:43:06 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube3d.h"

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
		if (key == -1 && valid_key(info, 0))
			return (nfree(line_key), E_NO_MORE_KEY);
		else if (key != KEY_C && key != KEY_F)
		{
			if (get_key_value(line_key, key, info) == E_NO_MORE_KEY)
				return (close(info->map_fd), nfree(line_key), E_NO_MORE_KEY);
		}
		else if (get_color(line_key, key, info) == E_WRONG_COLOR)
			return (close(info->map_fd), nfree(line_key), E_NO_MORE_KEY);
		nfree (line_key);
		line_key = get_next_line(info->map_fd);
	}
	return (E_NO_MORE_KEY);
}

int	init_info(t_info *info)
{
	int		i;

	i = -1;
	ft_memset(info, 0, sizeof(t_info));
	while (++i < 3)
	{
		info->ceiling[i] = -1;
		info->floor[i] = -1;
	}
	return (0);
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

int	parsing_cube(char *arg, t_info *info)
{
	int		result;

	if (check_format(arg, ".cub") == E_FORMAT)
		return (error_msg(E_FORMAT, NULL), 0);
	result = get_arg(arg, info);
	if (result == E_NO_MORE_KEY)
	{
		if (!valid_key(info, 1))
			return (0);
		else
			if (get_map(info) != SUCCESS)
				return (error_msg(E_INVALID_MAP, NULL), \
				freetab((info)->map), 0);
	}
	else if (result == E_CANT_OPEN)
		return (error_msg(E_CANT_OPEN, arg), 0);
	return (SUCCESS);
}
