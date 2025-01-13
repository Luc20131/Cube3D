/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:00:05 by sjean             #+#    #+#             */
/*   Updated: 2025/01/13 16:45:19 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cube3d.h"

char	*get_key_word(char *line)
{
	int		index;
	int		start;
	char	*str;

	index = skip_space(line);
	start = index;
	if (line[index] == '\0')
		return (0);
	else if (line[index] == '\n')
		return ("SKIP");
	while (line[index] && (line[index] != ' ' && line[index] != '	' && line[index] != '\n'))
		index++;
	if (!line[index])
		return (0);
	str = ft_substr(line, start, index - start);
	if (!str)
		return (0);
	return (str);
}

int	key_finder(char *line)
{
	char	*key;

	key = get_key_word(line);
	if (!key)
		return (error_msg(E_INVALID_LINE, line), -1);
	if (ft_strncmp(key, "SKIP", 4) == 0 && ft_strlen(key) == 4)
		return (SKIP);
	else if (ft_strncmp(key, "NO", 2) == 0 && ft_strlen(key) == 2)
		return (nfree(key), KEY_NO);
	else if (ft_strncmp(key, "SO", 2) == 0 && ft_strlen(key) == 2)
		return (nfree(key), KEY_SO);
	else if (ft_strncmp(key, "WE", 2) == 0 && ft_strlen(key) == 2)
		return (nfree(key), KEY_WE);
	else if (ft_strncmp(key, "EA", 2) == 0 && ft_strlen(key) == 2)
		return (nfree(key), KEY_EA);
	else if (ft_strncmp(key, "F", 1) == 0 && ft_strlen(key) == 1)
		return (nfree(key), KEY_F);
	else if (ft_strncmp(key, "C", 1) == 0 && ft_strlen(key) == 1)
		return (nfree(key), KEY_C);
	else
		return (error_msg(E_INVALID_LINE, key), nfree(key), -1);
}

int	assing_key_value(char *key_value, t_key key, t_info *info)
{
	if (key == KEY_NO)
	{
		if (info->texture_path[0][0] != '\0')
			return (error_msg(E_DUPLICATE_KEY, "NO"), 0);
		ft_strlcpy(info->texture_path[0], key_value, ft_strlen(key_value) + 1);
	}
	else if (key == KEY_SO)
	{
		if (info->texture_path[1][0] != '\0')
			return (error_msg(E_DUPLICATE_KEY, "SO"), 0);
		ft_strlcpy(info->texture_path[1], key_value, ft_strlen(key_value) + 1);
	}
	else if (key == KEY_WE)
	{
		if (info->texture_path[2][0] != '\0')
			return (error_msg(E_DUPLICATE_KEY, "WE"), 0);
		ft_strlcpy(info->texture_path[2], key_value, ft_strlen(key_value) + 1);
	}
	else if (key == KEY_EA)
	{
		if (info->texture_path[3][0] != '\0')
			return (error_msg(E_DUPLICATE_KEY, "EA"), 0);
		ft_strlcpy(info->texture_path[3], key_value, ft_strlen(key_value) + 1);
	}
	return (1);
}

int	get_key_value(char *key_v, t_key key, t_info *info)
{
	int		index;
	int		start;
	int		end;
	char	str[PATH_MAX];

	index = skip_key_word(key_v);
	start = index;
	while (!not_a_word(key_v[index]))
		index++;
	end = index;
	while (key_v[index] != '\n' && key_v[index] != '\0')
	{
		index += skip_space(&key_v[index]);
		while (!not_a_word(key_v[index]))
			index++;
		end = index;
	}
	ft_strlcpy(str, &key_v[start], (end + 1) - start);
	if (check_format(str, ".xpm") == E_FORMAT)
		return (error_msg(E_FORMAT, str), E_FORMAT);
	if (!assing_key_value(str, key, info))
		return (E_DUPLICATE_KEY);
	if (valid_key(info, 0))
		return (E_NO_MORE_KEY);
	return (SUCCESS);
}
