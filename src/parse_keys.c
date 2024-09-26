/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:00:05 by sjean             #+#    #+#             */
/*   Updated: 2024/09/26 18:20:36 by sjean            ###   ########.fr       */
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
	else if (key == KEY_F)
		ft_strlcpy(info->floor, key_value, ft_strlen(key_value) +1);
	else if (key == KEY_C)
		ft_strlcpy(info->ceiling, key_value, ft_strlen(key_value) +1);
	return (1);
}

int	not_a_word(char c)
{
	if (c != ' ' && c != '	' && c != '\n' && c != '\0')
		return (0);
	return (1);
}

int	get_key_value(char *key_v, t_key key, t_info *info)
{
	int		index;
	int		start;
	int		end;
	char	*str;

	index = skip_space(key_v);
	while (!not_a_word(key_v[index]))
		index++;
	index += skip_space(&key_v[index]);
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

int	key_finder(char *line, t_info *info)
{
	char	*key;

	(void)info;
	key = get_key_word(line);
	if (!key)
		return (1);
	if (ft_strncmp(key, "NO", 2) == 0 && ft_strlen(key) == 2)
		get_key_value(line, KEY_NO, info),ft_printf("NO: %s\n", info->texture_path[0]);
	else if (ft_strncmp(key, "SO", 2) == 0 && ft_strlen(key) == 2)
		get_key_value(line, KEY_SO, info),ft_printf("SO: %s\n", info->texture_path[1]);
	else if (ft_strncmp(key, "WE", 2) == 0 && ft_strlen(key) == 2)
		get_key_value(line, KEY_WE, info),ft_printf("WE: %s\n", info->texture_path[2]);
	else if (ft_strncmp(key, "EA", 2) == 0 && ft_strlen(key) == 2)
		get_key_value(line, KEY_EA, info),ft_printf("EA: %s\n", info->texture_path[3]);
	else if (ft_strncmp(key, "F", 1) == 0 && ft_strlen(key) == 1)
		get_key_value(line, KEY_F, info),ft_printf("F: %s\n", info->floor);
	else if (ft_strncmp(key, "C", 1) == 0 && ft_strlen(key) == 1)
		get_key_value(line, KEY_C, info),ft_printf("C: %s\n", info->ceiling);
	else
		return (free(key), 1);
	return (free(key), 1);
}

//read file and get the keys for texture and color =============================
int	get_arg(char *argv, t_info *info)
{
	char	*line_key;

	info->map_fd = open(argv, O_RDONLY);
	if (info->map_fd == -1)
		return (1);
	line_key = get_next_line(info->map_fd);
	while (line_key)
	{
		if (!key_finder(line_key, info))
			return (1);
		free (line_key);
		line_key = get_next_line(info->map_fd);
	}
	return (0);
}
