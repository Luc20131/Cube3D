/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:00 by sjean             #+#    #+#             */
/*   Updated: 2024/10/22 17:56:43 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	valid_key(t_info *info)
{
	int	i;
	int fd;

	i = -1;
	while (++i < 4)
	{
		if (!info->texture_path[i][0])
			return (0);
		if (check_format(info->texture_path[i], ".xpm") == E_FORMAT)
			return (0);
		fd = open(info->texture_path[i], O_RDONLY);
		if (fd == -1)
			return (0);
		close (fd);
	}
	i = -1;
	while (++i < 3)
	{
		if (info->ceiling[i] == -1)
			return (0);
		if (info->floor[i] == -1)
			return (0);
	}
	return (1);
}

void	error_msg(int error)
{
	ft_printf("Error\n");
	if (error == E_MALLOC)
		ft_printf("Malloc failed\n");
	if (error == E_WRONG_COLOR)
		ft_printf("Wrong color\n");
	if (error == E_WRONG_KEY)
		ft_printf("Texture invalid\n");
	if (error == E_INVALID_MAP)
		ft_printf("Invalid map\n");
	if (error == E_FORMAT)
		ft_printf("Invalid extension\n");
	if (error == E_CANT_OPEN)
		ft_printf("Can't open file\n");
}

int	check_map(t_info *info, t_list **head)
{
	int	result;

	if (init_map(info, *head) == E_MALLOC)
		return (ft_lstclear(head, free), E_MALLOC);
	if (!check_valid_chr_map(info->map))
		return (ft_lstclear(head, free), E_INVALID_MAP);
	result = parse_map(info->map, info->player);
	if (result == E_HOLE)
		return (ft_lstclear(head, free), E_HOLE);
	if (result == E_MALLOC)
		return (ft_lstclear(head, free), E_MALLOC);
	return (ft_lstclear(head, free), SUCCESS);
}

void	show_map(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'V')
				ft_printf("\033[32m");
			if (map[y][x] == 'X')
				ft_printf("\033[31m");
			ft_putchar_fd(map[y][x], 0);
			ft_printf("\033[0m");
		}
		ft_printf("\n");
	}
	usleep(10000);
}
