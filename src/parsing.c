/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:41:54 by sjean             #+#    #+#             */
/*   Updated: 2024/10/14 18:19:17 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"
#include "../headers/cube3d.h"

int	get_arg(char *argv, t_info *info)
{
	char	*line_key;
	int		key;

	info->map_fd = open(argv, O_RDONLY);
	if (info->map_fd == -1)
		return (1);
	line_key = get_next_line(info->map_fd);
	while (line_key)
	{
		key = key_finder(line_key);
		if (key == -1)
			return (free(line_key), E_NO_MORE_KEY);
		else if (key != KEY_C && key != KEY_F)
		{
			if (get_key_value(line_key, key, info) == E_NO_MORE_KEY)
				return (free(line_key), E_NO_MORE_KEY);
		}
		else if (get_color(line_key, key, info) == E_WRONG_COLOR)
			return (E_WRONG_COLOR);
		free (line_key);
		line_key = get_next_line(info->map_fd);
	}
	return (0);
}

int valid_key(t_info *info)
{
	int i;

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

void error_msg(int error)
{
	if (error == E_WRONG_COLOR)
		ft_printf("Error\nWrong color\n");
	if (error == E_WRONG_KEY)
		ft_printf("Error\nTexture invalid\n");
	if (error == E_INVALID_MAP)
		ft_printf("Error\nInvalid map\n");
}

t_info *init_info(void)
{
	int 	i;
	t_info	*info;

	i = -1;
	info = ft_calloc(1, sizeof(t_info));
	if (!info)
		return (NULL);
	ft_memset(info, 0, sizeof(t_info));
	while (++i < 3)
	{
		info->ceiling[i] = -1;
		info->floor[i] = -1;	
	}
	return (info);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	parsing_cube(char *arg)
{
	t_info	*info;
	int		result;
	int		i;

	info = init_info();
	if (!info)
		return (E_MALLOC);
	result = get_arg(arg, info);
	if (result == E_NO_MORE_KEY)
	{
		if (!valid_key(info))
			return (error_msg(E_WRONG_KEY), free(info), 0);
		else
			if (get_map(info) == E_INVALID_MAP)
				return (error_msg(E_INVALID_MAP), freetab(info->map), free(info), 0);
	}
	else if (result == E_WRONG_COLOR)
		return (error_msg(E_WRONG_COLOR), free(info), 0);
	ft_printf("NO %s\nSO %s\nWE %s\nEA %s\nF %d %d %d\nC %d %d %d\n",
	info->texture_path[0], info->texture_path[1], info->texture_path[2],
	info->texture_path[3], info->floor[0], info->floor[1], info->floor[2],
	info->ceiling[0], info->ceiling[1], info->ceiling[2]);
	i = -1;
	while (info->map[++i])
		ft_printf("%s\n", info->map[i]);
	ft_printf("Player x:%d y:%d\n", info->player.x, info->player.y);
	freetab(info->map);
	free(info);
	return (1);
}


