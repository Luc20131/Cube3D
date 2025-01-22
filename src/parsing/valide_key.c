/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:46:06 by sjean             #+#    #+#             */
/*   Updated: 2025/01/22 12:56:54 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_key_name(int key)
{
	if (key == KEY_NO)
		return ("NO");
	if (key == KEY_SO)
		return ("SO");
	if (key == KEY_EA)
		return ("EA");
	if (key == KEY_WE)
		return ("WE");
	return ("NULL");
}

int	valid_texture(t_info *info, int i, int print)
{
	int	fd;

	if (!info->texture_path[i][0])
		return (E_WRONG_KEY);
	if (check_format(info->texture_path[i], ".xpm") == E_FORMAT)
		return (E_NOT_XPM);
	if (print)
	{
		fd = open(info->texture_path[i], O_RDONLY);
		if (fd == -1)
			return (E_CANT_OPEN);
		close (fd);
	}
	return (SUCCESS);
}

int	check_color_nb(int countc, int countf, int print)
{
	if (countc > 1 || countf > 1)
	{
		if (countc == 3 && print)
			error_msg(E_NO_COLOR, "C");
		else if (countc > 1 && print)
			error_msg(E_WRONG_COLOR, "C");
		if (countf == 3 && print)
			error_msg(E_NO_COLOR, "F");
		else if (countf > 1 && print)
			error_msg(E_WRONG_COLOR, "F");
		return (0);
	}
	return (1);
}

int	valid_color(t_info *info, int print)
{
	int	i;
	int	countf;
	int	countc;

	i = -1;
	countf = 0;
	countc = 0;
	while (++i < 3)
	{
		if (info->ceiling[i] == -1)
			countc++;
		if (info->floor[i] == -1)
			countf++;
	}
	if (!check_color_nb(countc, countf, print))
		return (0);
	return (1);
}

int	valid_key(t_info *info, int print)
{
	int	i;
	int	result;

	i = -1;
	while (++i < 4)
	{
		result = valid_texture(info, i, print);
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
