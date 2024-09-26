/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:00:05 by sjean             #+#    #+#             */
/*   Updated: 2024/09/25 17:49:35 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"
#include "../headers/cube3d.h"

int skip_space(char *line)
{
	int i;

	i = -1;
	while (line[++i] == ' ' || line[i] == '	')
		;
	return (i);	
}

char *get_word(char *line)
{
	int		i;
	int		start;
	char	*tmp;

	i = skip_space(line);
	start = i;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	while (line[i] && (line[i] != ' ' && line[i] != '	'))
		i++;
	if (!line[i])
		return (0);
	tmp = ft_substr(line, start, i);
	if (!tmp)
		return (0);
	return (tmp);
}

int key_finder(char *line, t_info info)
{
	char *tmp;
	
	(void)info;
	tmp = get_word(line);
	if (!tmp)
		return (1);
	if (ft_strncmp(tmp, "NO", ft_strlen(tmp)) == 0)
		return (ft_printf("NO\n"));
	else if (ft_strncmp(tmp, "SO", ft_strlen(tmp)) == 0)
		return (ft_printf("SO\n"));
	else if (ft_strncmp(tmp, "WE", ft_strlen(tmp)) == 0)
		return (ft_printf("WE\n"));
	else if (ft_strncmp(tmp, "EA", ft_strlen(tmp)) == 0)
		return (ft_printf("EA\n"));
	else if (ft_strncmp(tmp, "F", ft_strlen(tmp)) == 0)
		return (ft_printf("F\n"));
	else if (ft_strncmp(tmp, "C", ft_strlen(tmp)) == 0)
		return (ft_printf("C\n"));
	else
		return (free(tmp), 0);
	return (0);
}

int get_arg(char *argv, t_info info)
{
	char	*line_key;
	
	info.map_fd = open(argv, O_RDONLY);
	if (info.map_fd == -1)
		return (1);
	line_key = get_next_line(info.map_fd);
	while (line_key)
	{
		if (!key_finder(line_key, info))
			return (1);
		free (line_key);
		line_key = get_next_line(info.map_fd);
	}
	return (0);
}
