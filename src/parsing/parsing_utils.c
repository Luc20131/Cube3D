/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:00 by sjean             #+#    #+#             */
/*   Updated: 2025/01/14 14:10:01 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		nfree(tab[i++]);
	nfree(tab);
}

void	error_msg_map(int error, char *content)
{
	if (error == E_INVALID_MAP)
		ft_printf("This file doesn't contain a map\n");
	if (error == E_TO_MANY_PLAYER)
		ft_printf("Invalid map\nTo nany player on the map\n");
	if (error == E_NO_PLAYER)
		ft_printf("Invalid map\nNo player on the map\n", content);
	if (error == E_INVALID_CHARACTER)
		ft_printf("Invalid map\n%c is not a valid character\n", content[0]);
	if (error == E_HOLE)
		ft_printf("Invalid map\nThe map is not surrounded by walls\n");
}

void	error_msg(int error, char *content)
{
	ft_printf("Error\n");
	if (error == E_MALLOC)
		ft_printf("Malloc failed\n");
	if (error == E_WRONG_COLOR)
		ft_printf("%s color is wrong\n", content);
	if (error == E_NO_COLOR)
		ft_printf("%s doesn't exist\n", content);
	if (error == E_WRONG_KEY)
		ft_printf("%s doesn't exist\n", content);
	if (error == E_FORMAT)
		ft_printf("%s\nInvalid extension\n", content);
	if (error == E_CANT_OPEN)
		ft_printf("%s can not be open\n", content);
	if (error == E_NOT_XPM)
		ft_printf("%s is not a xpm file\n", content);
	if (error == E_DUPLICATE_KEY)
		ft_printf("%s is already assigned\n", content);
	if (error == E_INVALID_LINE)
		ft_printf("%s is not a valide key", content);
	error_msg_map(error, content);
}

int	check_map(t_info *info, t_list **head)
{
	int	result;

	if (!*head)
		return (error_msg(E_INVALID_MAP, NULL), E_MALLOC);
	if (init_map(info, *head) == E_MALLOC)
		return (ft_lstclear(head, nfree), E_MALLOC);
	if (!check_valid_chr_map(info->map))
		return (ft_lstclear(head, nfree), E_INVALID_MAP);
	result = parse_map(info->map);
	if (result == E_HOLE)
		return (ft_lstclear(head, nfree), E_HOLE);
	if (result == E_MALLOC)
		return (ft_lstclear(head, nfree), E_MALLOC);
	return (ft_lstclear(head, nfree), SUCCESS);
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
}
