/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:52:36 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:57:46 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_map(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'V')
				map[y][x] = '0';
			if (map[y][x] == ' ')
				map[y][x] = '1';
		}
	}
}

int	check_holes(char **map, t_pos pos)
{
	if (pos.y - 1 < 0 || !map[pos.y - 1] || map[pos.y - 1][pos.x] == ' ' || \
		pos.x - 1 < 0 || !map[pos.y][pos.x + 1] || \
		map[pos.y][pos.x + 1] == ' ' || \
		!map[pos.y + 1] || map[pos.y + 1][pos.x] == ' ' || \
		!map[pos.y][pos.x - 1] || map[pos.y][pos.x - 1] == ' ')
	{
		map[pos.y][pos.x] = 'X';
		return (0);
	}
	return (1);
}

int	parse_map(char **map)
{
	t_pos	pos;

	pos.y = -1;
	while (map[++pos.y])
	{
		pos.x = -1;
		while (map[pos.y][++pos.x])
		{
			if (cmp_n_elt(map[pos.y][pos.x], "NESW0") && !check_holes(map, pos))
				return (show_map(map), error_msg(E_HOLE, NULL), E_HOLE);
			else if (cmp_n_elt(map[pos.y][pos.x], "0"))
				map[pos.y][pos.x] = 'V';
		}
	}
	return (clean_map(map), SUCCESS);
}
