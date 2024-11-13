/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:35:14 by sjean             #+#    #+#             */
/*   Updated: 2024/11/13 01:49:19 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_dir(t_stats **stats, char **map, t_pos pos)
{
	if (pos.y - 1 >= 0 && map[pos.y - 1] && map[pos.y - 1][pos.x] == '0')
		(*stats)->dir++;
	if (map[pos.y][pos.x + 1] && map[pos.y][pos.x + 1] == '0')
		(*stats)->dir++;
	if (map[pos.y + 1] && map[pos.y + 1][pos.x] == '0')
		(*stats)->dir++;
	if (pos.x - 1 >= 0 && map[pos.y][pos.x - 1] && map[pos.y][pos.x - 1] == '0')
		(*stats)->dir++;
	return (SUCCESS);
}

int	check_holes(t_stats **stats, char **map, t_pos pos)
{
	(void)stats;
	if (pos.y - 1 < 0 || !map[pos.y - 1] || map[pos.y - 1][pos.x] == ' ' || \
		pos.x - 1 < 0 || !map[pos.y][pos.x + 1] || \
		map[pos.y][pos.x + 1] == ' ' || \
		!map[pos.y + 1] || map[pos.y + 1][pos.x] == ' ' || \
		!map[pos.y][pos.x - 1] || map[pos.y][pos.x - 1] == ' ')
	{
		map[pos.y][pos.x] = 'X';
		return (E_HOLE);
	}
	return (SUCCESS);
}

int	choose_dir(t_stats **stats, char **map, t_pos pos)
{
	if (map[pos.y - 1][pos.x] && map[pos.y - 1][pos.x] == '0')
	{
		(*stats)->dir--;
		pos.y = pos.y -1;
		return (stats_add_back(stats, pos));
	}
	else if (map[pos.y][pos.x + 1] && map[pos.y][pos.x + 1] == '0')
	{
		(*stats)->dir--;
		pos.x = pos.x + 1;
		return (stats_add_back(stats, pos));
	}
	else if (map[pos.y + 1][pos.x] && map[pos.y + 1][pos.x] == '0')
	{
		(*stats)->dir--;
		pos.y = pos.y + 1;
		return (stats_add_back(stats, pos));
	}
	else if (map[pos.y][pos.x - 1] && map[pos.y][pos.x - 1] == '0')
	{
		(*stats)->dir--;
		pos.x = pos.x -1;
		return (stats_add_back(stats, pos));
	}
	return (SUCCESS);
}

int	get_back(t_stats **stats, char **map)
{
	while ((*stats)->prev && (*stats)->dir == 0)
	{
		*stats = (*stats)->prev;
		nfree((*stats)->next);
		(*stats)->next = NULL;
		if ((*stats)->dir != 0)
		{
			(*stats)->dir = 0;
			get_dir(stats, map, (*stats)->pos);
		}
	}
	return (SUCCESS);
}

int	parse_map(char **map, t_pos pos)
{
	t_stats	*stats;
	int		result;

	result = init_first(&stats, map, pos);
	if (result == E_HOLE)
		return (E_HOLE);
	if (result == E_MALLOC)
		return (E_MALLOC);
	while (stats)
	{
		get_dir(&stats, map, stats->pos);
		if (check_holes(&stats, map, stats->pos) == E_HOLE)
			return (show_map(map), free_stats(&stats), E_HOLE);
		if (!cmp_n_elt(map[stats->pos.y][stats->pos.x], "NESW"))
			map[stats->pos.y][stats->pos.x] = 'V';
		if (stats->dir == 0)
			get_back(&stats, map);
		if (choose_dir(&stats, map, stats->pos) == E_MALLOC)
			return (free_stats(&stats), E_MALLOC);
		if (cmp_n_elt(map[stats->pos.y][stats->pos.x], "NESW") && !stats->next)
			return (show_map(map), clean_map(map, &stats), SUCCESS);
		stats = stats->next;
	}
	return (show_map(map), clean_map(map, &stats), SUCCESS);
}

		// int i;
		// i = -1;
		// while (map[++i])
		// ft_printf("%s\n", map[i]);
