/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:35:14 by sjean             #+#    #+#             */
/*   Updated: 2024/10/15 19:13:56 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include "../headers/parsing.h"

int get_the_big_one(t_list *list)
{
	size_t size;

	size = 0;
	while (list)
	{
		if (size < ft_strlen(list->content))
			size = ft_strlen(list->content);
		list = list->next;
	}
	return ((int)size);
}

int find_player(t_info *info)
{
	int x;
	int y;

	y = -1;
	while (info->map[++y])
	{
		x = -1;
		while (info->map[y][++x])
		{
			if (cmp_n_elt(info->map[y][x], "NESW"))		
			{
				info->player.x = x;
				info->player.y = y;
				return (1);
			}
		}
	}
	info->player.x = -1;
	info->player.y = -1;
	return (0);
}

int init_map(t_info *info, t_list *list)
{
	int	size_tab;
	int	size_line;
	int	i;
	int	j;

	i = -1;
	size_tab = ft_lstsize(list);
	size_line = get_the_big_one(list) -1;
	info->map = ft_calloc(size_tab + 1, sizeof(char *));
	if (!info->map)
		return (E_MALLOC);
	while (list)
	{
		info->map[++i] = ft_calloc(size_line + 1, sizeof(char));
		ft_memset(info->map[i], ' ', size_line);
		j = -1;
		while (((char *)list->content)[++j] && ((char *)list->content)[j] != '\n')
			info->map[i][j] = ((char *)list->content)[j];
		list = list->next;
	}
	find_player(info);
	return (1);
}

int cmp_n_elt(char c, char *cmp)
{
	int	elt;

	elt = -1;
	while (cmp[++elt])
		if (cmp[elt] == c)
			return (1);
	return (0);
}

int check_valid_chr_map(char **map)
{
	int	x;
	int	y;
	int	player;
	
	y = -1;
	player = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!cmp_n_elt(map[y][x], "NESW01 "))
				return (0);
			if (cmp_n_elt(map[y][x], "NESW"))
				player++;
		}
	}
	if (player != 1)
		return (0);
	return (1);
}

int get_dir(t_stats **stats, char **map, t_pos pos)
{
	if (map[pos.y - 1][pos.x] && map[pos.y - 1][pos.x] == '0')
		(*stats)->dir++;
	if (map[pos.y][pos.x + 1] && map[pos.y][pos.x + 1] == '0')
		(*stats)->dir++;
	if (map[pos.y + 1][pos.x] && map[pos.y + 1][pos.x] == '0')
		(*stats)->dir++;
	if (map[pos.y][pos.x - 1] && map[pos.y][pos.x - 1] == '0')
		(*stats)->dir++;
	return (SUCCESS);
}

int check_holes(t_stats **stats, char **map, t_pos pos)
{
	(void)stats;
	if (!map[pos.y - 1][pos.x] || map[pos.y - 1][pos.x] == ' ' || \
		!map[pos.y][pos.x + 1] || map[pos.y][pos.x + 1] == ' ' || \
		!map[pos.y + 1][pos.x] || map[pos.y + 1][pos.x] == ' ' || \
		!map[pos.y][pos.x - 1] || map[pos.y][pos.x - 1] == ' ')
		{
			map[pos.y][pos.x] = 'X';
			return (E_HOLE);
		}
	return (SUCCESS);
}

int	stats_add_back(t_stats **stats, t_pos pos)
{
	t_stats *newstats;

	newstats = ft_calloc(1, sizeof(t_stats));
	if (!newstats)
		return (E_MALLOC);
	ft_memset(newstats, 0, sizeof(t_stats));
	newstats->prev = *stats;
	newstats->pos = pos;
	
		(*stats)->next = newstats;
	return (SUCCESS);
}

int choose_dir(t_stats **stats, char **map, t_pos pos)
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

int get_back(t_stats **stats, char **map)
{
	while ((*stats)->prev && (*stats)->dir == 0)
	{
		ft_printf("return\n");
		*stats = (*stats)->prev;
		if ((*stats)->dir != 0)
		{
			(*stats)->dir = 0;
			get_dir(stats, map, (*stats)->pos);
		}
	}
	return (SUCCESS);
}

int init_first(t_stats **stats, char **map, t_pos pos)
{
	*stats = ft_calloc(1, sizeof(t_stats));
	(*stats)->pos = pos;
	get_dir(stats, map, (*stats)->pos);
	if (check_holes(&(*stats), map, (*stats)->pos) == E_HOLE)
		return (E_HOLE);
	if (choose_dir(stats, map, (*stats)->pos) == E_MALLOC)
		return (E_MALLOC);
	if ((*stats)->next)
		(*stats) = (*stats)->next;
	return (SUCCESS);
}
void show_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'V')
			{
				printf("\001\033[1;34m\002");
				printf("%c", map[i][j]);
				printf("\001\033[0m\002");
			}
			else if (map[i][j] == 'X')
			{
				printf("\001\033[32m\002");
				printf("%c", map[i][j]);
				printf("\001\033[0m\002");
			}
			else
			{
				printf("%c", map[i][j]);
			}
		}
		ft_printf("\n");
	}
	// ft_printf("dir :%d\npos x:%d y:%d\n", stats->dir, stats->pos.x, stats->pos.y);
	usleep(100000);
}

int	parse_map(char **map, t_pos pos)
{
	t_stats *stats;
	int 	result;

	result = init_first(&stats, map, pos);
	if (result == E_HOLE)
		return (E_HOLE);
	if (result == E_MALLOC)
		return (E_MALLOC);
	while (42)
	{
		show_map(map);
		get_dir(&stats, map, stats->pos);
		if (check_holes(&stats, map, stats->pos) == E_HOLE)
			return (E_HOLE);
		if (!cmp_n_elt(map[stats->pos.y][stats->pos.x], "NESW"))
			map[stats->pos.y][stats->pos.x] = 'V';
		if (stats->dir == 0)
			get_back(&stats, map);
		if (choose_dir(&stats, map, stats->pos) == E_MALLOC)
			return (E_MALLOC);
		if (cmp_n_elt(map[stats->pos.y][stats->pos.x], "NESW"))
			return (ft_printf("FIN"), SUCCESS);
		stats = stats->next;
	}
	return (SUCCESS);
}

int get_map(t_info *info)
{
	char	*line;
	t_list	*tab;
	t_list	*head;

	line = get_next_line(info->map_fd);
	head = NULL;
	while (line)
	{
		if (line[0] != '\n')
		{
			tab = ft_lstnew(line);
			if (head)
				ft_lstadd_back(&head, tab);
			else
				head = tab;
			tab = tab->next;
		}
		line = get_next_line(info->map_fd);
	}
	init_map(info, head);
	ft_lstclear(&head, free);
	if (!check_valid_chr_map(info->map))
		return (E_INVALID_MAP);
	parse_map(info->map, info->player);
	return (SUCCESS);
}
