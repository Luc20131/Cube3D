/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:00:05 by sjean             #+#    #+#             */
/*   Updated: 2024/10/02 18:00:13 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"
#include "../headers/cube3d.h"

int	skip_space(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ' || line[i] == '	')
		;
	return (i);
}

char	*get_key_word(char *line)
{
	int		index;
	int		start;
	char	*str;

	index = skip_space(line);
	start = index;
	if (line[index] == '\n' || line[index] == '\0')
		return (0);
	while (line[index] && (line[index] != ' ' && line[index] != '	'))
		index++;
	if (!line[index])
		return (0);
	str = ft_substr(line, start, index - start);
	if (!str)
		return (0);
	return (str);
}

int	assing_key_value(char *key_value, t_key key, t_info *info)
{
	if (key == KEY_NO)
		ft_strlcpy(info->texture_path[0], key_value, ft_strlen(key_value) +1);
	else if (key == KEY_SO)
		ft_strlcpy(info->texture_path[1], key_value, ft_strlen(key_value) +1);
	else if (key == KEY_WE)
		ft_strlcpy(info->texture_path[2], key_value, ft_strlen(key_value) +1);
	else if (key == KEY_EA)
		ft_strlcpy(info->texture_path[3], key_value, ft_strlen(key_value) +1);
	return (1);
}

int	not_a_word(char c)
{
	if (c != ' ' && c != '	' && c != '\n' && c != '\0')
		return (0);
	return (1);
}

int skip_key_word(char *key_v)
{
	int		index;

	index = skip_space(key_v);
	while (!not_a_word(key_v[index]))
		index++;
	index += skip_space(&key_v[index]);
	return (index);
}

int	get_key_value(char *key_v, t_key key, t_info *info)
{
	int		index;
	int		start;
	int		end;
	char	*str;

	index = skip_key_word(key_v);
	start = index;
	while (!not_a_word(key_v[index]))
		index++;
	end = index;
	while (key_v[index] != '\n' && key_v[index] != '\0')
	{
		end = index;
		index += skip_space(&key_v[index]);
		while (!not_a_word(key_v[index]))
			index++;
	}
	str = ft_substr(key_v, start, end - start);
	if (!str)
		return (E_MALLOC);
	assing_key_value(str, key, info);
	return (1);
}

int	key_finder(char *line)
{
	char	*key;

	key = get_key_word(line);
	if (!key)
		return (-1);
	if (ft_strncmp(key, "NO", 2) == 0 && ft_strlen(key) == 2)
		return(free(key), KEY_NO);
	else if (ft_strncmp(key, "SO", 2) == 0 && ft_strlen(key) == 2)
		return(free(key), KEY_SO);
	else if (ft_strncmp(key, "WE", 2) == 0 && ft_strlen(key) == 2)
		return(free(key), KEY_WE);
	else if (ft_strncmp(key, "EA", 2) == 0 && ft_strlen(key) == 2)
		return(free(key), KEY_EA);
	else if (ft_strncmp(key, "F", 1) == 0 && ft_strlen(key) == 1)
		return(free(key), KEY_F);
	else if (ft_strncmp(key, "C", 1) == 0 && ft_strlen(key) == 1)
		return(free(key), KEY_C);
	else
		return (free(key), -1);
	return (free(key), -1);
}
