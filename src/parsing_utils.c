/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:19:00 by sjean             #+#    #+#             */
/*   Updated: 2024/10/16 18:09:11 by sjean            ###   ########.fr       */
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

	i = -1;
	while (++i < 4)
	{
		if (!info->texture_path[i][0])
			return (0);
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
	if (error == E_WRONG_COLOR)
		ft_printf("Error\nWrong color\n");
	if (error == E_WRONG_KEY)
		ft_printf("Error\nTexture invalid\n");
	if (error == E_INVALID_MAP)
		ft_printf("Error\nInvalid map\n");
	if (error == E_FORMAT)
		ft_printf("Error\nInvalid extension\n");
	if (error == E_CANT_OPEN)
		ft_printf("Error\nCan't open file\n");
}
