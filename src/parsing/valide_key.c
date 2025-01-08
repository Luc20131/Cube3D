/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:46:06 by sjean             #+#    #+#             */
/*   Updated: 2025/01/08 20:43:18 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *get_key_name(int key)
{
	if (key == KEY_NO)
		return ("NO");
	if (key == KEY_SO)
		return ("SO");
	if (key == KEY_EA)
		return ("EA");
	if (key == KEY_WE)
		return ("WE");
	return ("");
}

int valid_texture(t_info *info, int i)
{
	int	fd;

	if (!info->texture_path[i][0])
		return (E_WRONG_KEY);
	if (check_format(info->texture_path[i], ".xpm") == E_FORMAT)
		return (E_NOT_XPM);
	fd = open(info->texture_path[i], O_RDONLY);
	if (fd == -1)
		return (E_CANT_OPEN);
	close (fd);
	return (SUCCESS);
}

int valid_color(t_info *info, int print)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (info->ceiling[i] == -1)
		{
			if (print)
				error_msg(E_WRONG_COLOR, "C");
			return (0);
		}
		if (info->floor[i] == -1)
		{
			if (print)
				error_msg(E_WRONG_COLOR, "F");
			return (0);
		}
	}
	return (1);
}

int	valid_key(t_info *info, int print)
{
	int	i;
	int result;
	
	i = -1;
	while (++i < 4)
	{
		result = valid_texture(info, i);
		if (result != SUCCESS)
		{
			if (print)
				error_msg(result, get_key_name(i));
			return (0);
		}
	}
	if (!valid_color(info, print))
		return (0);
	return (1);
}
