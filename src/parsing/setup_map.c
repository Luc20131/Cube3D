/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:37:41 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:58:07 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_chr_map(char **map)
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
				return (error_msg(E_INVALID_CHARACTER, &map[y][x]), 0);
			if (cmp_n_elt(map[y][x], "NESW"))
				player++;
		}
	}
	if (player > 1)
		return (error_msg(E_TO_MANY_PLAYER, NULL), 0);
	else if (player < 1)
		return (error_msg(E_NO_PLAYER, NULL), 0);
	return (1);
}

int	get_the_big_one(t_list *list)
{
	size_t	size;

	size = 0;
	while (list)
	{
		if (size < ft_strlen(list->content))
			size = ft_strlen(list->content);
		list = list->next;
	}
	return ((int)size);
}

int	find_player(t_info *info)
{
	int	x;
	int	y;

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

int	init_map(t_info *info, t_list *list)
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
		if (!info->map[i])
			return (E_MALLOC);
		ft_memset(info->map[i], ' ', size_line);
		j = -1;
		while (((char *)list->content)[++j] && (((char *)list->content)[j] \
		!= '\n' && ((char *)list->content)[j] != '\r'))
			info->map[i][j] = ((char *)list->content)[j];
		list = list->next;
	}
	find_player(info);
	return (1);
}

int	get_map(t_info *info)
{
	char	*line;
	t_list	*tab;
	t_list	*head;
	int		first;

	line = get_next_line(info->map_fd);
	head = NULL;
	first = 0;
	while (line)
	{
		if (line[0] != '\n' || first == 1)
		{
			first = 1;
			tab = ft_lstnew(line);
			if (head)
				ft_lstadd_back(&head, tab);
			else
				head = tab;
			tab = tab->next;
		}
		else
			nfree(line);
		line = get_next_line(info->map_fd);
	}
	return (close(info->map_fd), check_map(info, &head));
}
