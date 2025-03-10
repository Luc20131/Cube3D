/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:00:39 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:57:25 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_value(char *key_v)
{
	int	i;
	int	dest;

	i = -1;
	dest = 0;
	while (ft_isdigit(key_v[++i]))
		dest = dest * 10 + (key_v[i] - 48);
	if (key_v[i] != ' ' && key_v[i] != '	'\
	&& key_v[i] != '\n' && key_v[i] != '\0' && key_v[i] != ',' \
	&& key_v[i] != '\r')
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

int	increase_index(int *index, char *key_v, int key)
{
	static int	comma = 0;
	static int	enum_key = -1;

	if (enum_key != key)
	{
		comma = 0;
		enum_key = key;
	}
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
			return (error_msg(E_WRONG_COLOR, key_v), E_WRONG_COLOR);
		if (key == KEY_C)
			info->ceiling[nb] = tmp;
		else
			info->floor[nb] = tmp;
		nb += (!key_v[index] || key_v[index] != '\n');
		increase_index(&index, key_v, key);
		if (old_nb == nb || index == -1)
			return (error_msg(E_WRONG_COLOR, key_v), E_WRONG_COLOR);
	}
	if (key_v[index] != '\n' && key_v[index] != '\r')
		return (E_WRONG_COLOR);
	return (1);
}
