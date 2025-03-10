/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:55:06 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:57:36 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_stats(t_stats **stats)
{
	t_stats	*tmp;

	while ((*stats)->prev)
		*stats = (*stats)->prev;
	while (*stats)
	{
		tmp = *stats;
		(*stats) = (*stats)->next;
		nfree (tmp);
	}
}

void	clean_map(char **map, t_stats **stats)
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
	free_stats(stats);
}

int	stats_add_back(t_stats **stats, t_pos pos)
{
	t_stats	*newstats;

	newstats = ft_calloc(1, sizeof(t_stats));
	if (!newstats)
		return (E_MALLOC);
	ft_memset(newstats, 0, sizeof(t_stats));
	newstats->prev = *stats;
	newstats->pos = pos;
	(*stats)->next = newstats;
	return (SUCCESS);
}

int	cmp_n_elt(char c, char *cmp)
{
	int	elt;

	elt = -1;
	while (cmp[++elt])
		if (cmp[elt] == c)
			return (1);
	return (0);
}

t_pos	size_map(char **map)
{
	t_pos	size;
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	size.y = i;
	size.x = (ft_strlen(map[0]));
	return (size);
}
