/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_autotile_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:28:03 by sjean             #+#    #+#             */
/*   Updated: 2025/01/21 14:58:19 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cube3d.h"

int	*x_dir(int c[9], t_pos pos, t_mlx g, t_pos map_size)
{
	if (pos.x -1 >= 0 && pos.y -1 >= 0 && g.map[pos.x -1][pos.y -1] == '0')
		c[0] = '0' - 48;
	else if (pos.x -1 >= 0 && pos.y -1 >= 0 && g.map[pos.x -1][pos.y -1] == '1')
		c[0] = '1' - 48;
	if (pos.x -1 >= 0 && pos.y + 1 < map_size.x && \
	g.map[pos.x -1][pos.y + 1] == '0')
		c[2] = '0' - 48;
	else if (pos.x -1 >= 0 && pos.y + 1 < map_size.x && \
	g.map[pos.x -1][pos.y + 1] == '1')
		c[2] = '1' - 48;
	if (pos.x + 1 < map_size.y && pos.y + 1 < map_size.x && \
	g.map[pos.x + 1][pos.y + 1] == '0')
		c[8] = '0' - 48;
	else if (pos.x + 1 < map_size.y && pos.y + 1 < map_size.x && \
	g.map[pos.x + 1][pos.y + 1] == '1')
		c[8] = '1' - 48;
	if (pos.x + 1 < map_size.y && pos.y -1 >= 0 && \
	g.map[pos.x + 1][pos.y -1] == '0')
		c[6] = '0' - 48;
	else if ((pos.x + 1 < map_size.y && pos.y -1 >= 0 && \
	g.map[pos.x + 1][pos.y -1] == '1') || (pos.x + 1 >= map_size.y))
		c[6] = '1' - 48;
	return (c);
}

int	*plus_dir(int c[9], t_pos pos, t_mlx g, t_pos map_size)
{
	if (pos.x -1 >= 0)
		if (g.map[pos.x -1][pos.y] == '0')
			c = fill_dir_h(c, g.map, (t_pos){pos.x -1, pos.y}, (t_pos){0, 3});
	if (pos.x + 1 < map_size.y)
		if (g.map[pos.x + 1][pos.y] == '0')
			c = fill_dir_h(c, g.map, (t_pos){pos.x + 1, pos.y}, \
					(t_pos){6, 9});
	if (pos.y -1 >= 0)
		if (g.map[pos.x][pos.y - 1] == '0')
			fill_dir_v(c, g.map, (t_pos){pos.x, pos.y - 1}, (t_pos){0, 7});
	if (pos.y + 1 < map_size.x)
		if (g.map[pos.x][pos.y + 1] == '0')
			fill_dir_v(c, g.map, (t_pos){pos.x, pos.y + 1}, (t_pos){2, 9});
	c = face_corner_h(c, pos, g, g.map);
	if (c[3] == 1 && c[5] == 1 && c[2] == 1 && c[7] == 1)
		c = x_dir(c, pos, g, map_size);
	return (c);
}

int *init_dir(int c[9], t_pos pos, t_mlx g, t_pos map_size)
{
	int	i;

	i = -1;
	c[4] = g.map[pos.x][pos.y] -48;
	if (c[4] == 1)
		c = plus_dir(c, pos, g, map_size);
	else if (c[4] == 0)
	{
		while (++i < 9)
			c[i] = 0;
		if (pos.x -1 >= 0 && g.map[pos.x -1][pos.y] == '1')
			c = fill_dir_h(c, g.map, (t_pos){pos.x -1, pos.y}, (t_pos){0, 3});
	}
	return (0);
}

int	autotile_dir(char **map, t_mlx *g, int *t, t_pos pos)
{
	int		i;
	int		dir[9];
	t_pos	map_size;

	map_size = size_map(map);
	i = -1;
	while (++i < 9)
		dir[i] = 1;
	init_dir(dir, pos, *g, map_size);
	*t = (1 * dir[0] + 2 * dir[1] + 4 * dir[2] + 8 * dir[3] + \
		16 * dir[4] + 32 * dir[5] + 64 * dir[6] + 128 * dir[7] + 256 * dir[8]);
	return (0);
}

int	autotile_generator(char **map, t_mlx *g)
{
	int		h;
	int		w;
	int		i;
	int		size;
	t_pos	map_size;

	map_size = size_map(g->map);
	i = -1;
	h = -1;
	size = map_size.y * map_size.x;
	g->stats_tile = ft_calloc(size, sizeof(int *));
	if (!g->stats_tile)
		return (1);
	while (map[++h])
	{
		w = -1;
		while (map[h][++w] != '\0')
			if (autotile_dir(map, g, &g->stats_tile[++i], (t_pos){h, w}))
					return (nfree(g->stats_tile), 1);
	}
	return (0);
}
