/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_autotile_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:22:29 by sjean             #+#    #+#             */
/*   Updated: 2024/11/13 00:00:59 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"

int	*fill_dir_h(int *c, char **map, t_pos pos, t_pos fill)
{
	while (fill.x < fill.y)
		c[fill.x++] = map[pos.x][pos.y] - 48;
	return (c);
}

int	*fill_dir_v(int *c, char **map, t_pos pos, t_pos fill)
{
	while (fill.x < fill.y)
	{
		c[fill.x] = map[pos.x][pos.y] - 48;
		fill.x += 3;
	}
	return (c);
}

int	*l_corner_dir(int *c, t_pos pos, t_mlx g, char **map)
{
	t_pos	map_size;

	map_size = size_map(g.map);
	if (pos.x + 1 < map_size.y && pos.y + 1 < map_size.x && \
			pos.x - 1 >= 0 && pos.y - 1 >= 0)
	{
		if (c[0] == 0 && c[1] == 0 && c[2] == 0 && c[3] == 0 && c[6] == 0 \
		&& c[5] == 1 && c[7] == 1 && map[pos.x + 1][pos.y + 1] == '0')
			c[8] = 0;
		else if (c[0] == 0 && c[1] == 0 && c[2] == 0 && c[5] == 0 && c[8] == 0 \
		&& c[3] == 1 && c[7] == 1 && map[pos.x + 1][pos.y - 1] == '0')
			c[6] = 0;
		else if (c[6] == 0 && c[7] == 0 && c[8] == 0 && c[3] == 0 && c[0] == 0 \
		&& c[1] == 1 && c[5] == 1 && map[pos.x - 1][pos.y + 1] == '0')
			c[2] = 0;
		else if (c[6] == 0 && c[7] == 0 && c[8] == 0 && c[5] == 0 && c[2] == 0 \
		&& c[1] == 1 && c[3] == 1 && map[pos.x - 1][pos.y - 1] == '0')
			c[0] = 0;
	}
	return (c);
}

int	*face_corner_v(int *c, t_pos pos, t_mlx g, char **map)
{
	t_pos	map_size;

	map_size = size_map(g.map);
	if (pos.x + 1 < map_size.y && pos.y + 1 < map_size.x && \
			pos.x - 1 >= 0 && pos.y - 1 >= 0)
	{
		if (c[0] == 0 && c[3] == 0 && c[6] == 0 && c[1] == 1 && c[7] == 1 \
		&& c[5] == 1)
		{
			if (map[pos.x - 1][pos.y + 1] == '0')
				c[2] = 0;
			if (map[pos.x + 1][pos.y + 1] == '0')
				c[8] = 0;
		}
		else if (c[2] == 0 && c[5] == 0 && c[8] == 0 && c[1] == 1 && c[7] == 1 \
		&& c[3] == 1)
		{
			if (map[pos.x - 1][pos.y - 1] == '0')
				c[0] = 0;
			if (map[pos.x + 1][pos.y - 1] == '0')
				c[6] = 0;
		}
	}
	c = l_corner_dir(c, pos, g, map);
	return (c);
}

int	*face_corner_h(int *c, t_pos pos, t_mlx g, char **map)
{
	t_pos	map_size;

	map_size = size_map(g.map);
	if (pos.x + 1 < map_size.y && pos.y + 1 < map_size.x && \
			pos.x - 1 >= 0 && pos.y - 1 >= 0)
	{
		if (c[0] == 0 && c[1] == 0 && c[2] == 0 && c[3] == 1 && c[5] == 1 \
		&& c[7] == 1)
		{
			if (map[pos.x + 1][pos.y + 1] == '0')
				c[8] = 0;
			if (map[pos.x + 1][pos.y - 1] == '0')
				c[6] = 0;
		}
		else if (c[6] == 0 && c[7] == 0 && c[8] == 0 && c[3] == 1 && c[5] == 1 \
		&& c[1] == 1)
		{
			if (map[pos.x - 1][pos.y + 1] == '0')
				c[2] = 0;
			if (map[pos.x - 1][pos.y - 1] == '0')
				c[0] = 0;
		}
	}
	c = face_corner_v(c, pos, g, map);
	return (c);
}
