/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:17:18 by sjean             #+#    #+#             */
/*   Updated: 2024/11/13 01:49:19 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parsing.h"

int	skip_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ' || line[i] == '	')
		;
	return (i);
}

int	not_a_word(char c)
{
	if (c != ' ' && c != '	' && c != '\n' && c != '\0')
		return (0);
	return (1);
}

int	skip_key_word(char *key_v)
{
	int		index;

	index = skip_space(key_v);
	while (!not_a_word(key_v[index]))
		index++;
	index += skip_space(&key_v[index]);
	return (index);
}
