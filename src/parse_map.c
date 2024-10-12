/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:35:14 by sjean             #+#    #+#             */
/*   Updated: 2024/10/12 19:00:13 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include "../headers/parsing.h"

int init_map(t_info *info, t_list *list)
{
	return (0);
}

int get_map(t_info *info)
{
	char	*line;
	t_list	*tab;
	t_list	*head;

	line = get_next_line(info->map_fd);
	tab = ft_lstnew(NULL);
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
	return (0);
}
