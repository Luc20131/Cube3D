/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:00:39 by sjean             #+#    #+#             */
/*   Updated: 2024/10/19 19:56:39 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include "../headers/parsing.h"

int	get_color_value(char *key_v)
{
	int	i;
	int	dest;

	i = -1;
	dest = 0;
	while (ft_isdigit(key_v[++i]))
		dest = dest * 10 + (key_v[i] - 48);
	if (key_v[i] != ' ' && key_v[i] != '	'\
	&& key_v[i] != '\n' && key_v[i] != '\0' && key_v[i] != ',')
		return (-1);
	if (dest < 0 || dest > 255)
		return (-1);
	else
		return (dest);
}

int	skip_numbers(char *key_v)
{
	int	i;

	i = -1;
	while (ft_isdigit(key_v[++i]))
		;
	return (i);
}

int	increase_index(int *index, char *key_v)
{
	static int comma = 0;

	*index += skip_numbers(&key_v[*index]);
	*index += skip_space(&key_v[*index]);
	if (key_v[*index] == ',')
	{
		(*index)++;
		comma++;
	}
	*index += skip_space(&key_v[*index]);
	if (key_v[*index] == ',' || comma > 2)
		*index = -1;
	return (0);
}

int	get_color(char *key_v, t_key key, t_info *info)
{
	int	nb;
	int	old_nb;
	int	tmp;
	int	index;

	nb = 0;
	index = skip_key_word(key_v);
	while (nb < 3)
	{
		old_nb = nb;
		tmp = get_color_value(&key_v[index]);
		if (tmp == -1)
			return (E_WRONG_COLOR);
		if (key == KEY_C)
			info->ceiling[nb] = tmp;
		else
			info->floor[nb] = tmp;
		nb += (!key_v[index] || key_v[index] != '\n');
		increase_index(&index, key_v);
		if (old_nb == nb || index == -1)
			return (E_WRONG_COLOR);
	}
	if (key_v[index] != '\n')
		return (E_WRONG_COLOR);
	return (1);
}
