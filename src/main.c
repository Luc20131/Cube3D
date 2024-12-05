/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:52:12 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/29 15:23:00 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <stdio.h>

#include "cube3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "parsing.h"
#include "../minilibx-linux/mlx_int.h"
#include "../minilibx-linux/mlx.h"

enum
{
	NORTH = -1,
	EAST,
	SOUTH,
	WEST,
};
void	map(t_mlx *vars);
int		check_collision(t_pos index, const t_mlx *vars, char direction);

int	is_player(const char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	tick(t_mlx *vars)
{
	if (vars->player_data.movement.forward)
	{
		vars->player_data.float_pos.x += (PLAYER_SPEED * vars->ray.dir_x);
		vars->player_data.float_pos.y += (PLAYER_SPEED * vars->ray.dir_y);
	}
	else if (vars->player_data.movement.backward)
	{
		vars->player_data.float_pos.x -= (PLAYER_SPEED * vars->ray.dir_x);
		vars->player_data.float_pos.y -= (PLAYER_SPEED * vars->ray.dir_y);
	}
	else if (vars->player_data.movement.right)
	{
		vars->player_data.float_pos.x -= (PLAYER_SPEED * vars->ray.dir_y);
		vars->player_data.float_pos.y += (PLAYER_SPEED * vars->ray.dir_x);
	}
	else if (vars->player_data.movement.left)
	{
		vars->player_data.float_pos.x += (PLAYER_SPEED * vars->ray.dir_y);
		vars->player_data.float_pos.y -= (PLAYER_SPEED * vars->ray.dir_x);
	}
	player_pos_update(vars, vars->map);
	map(vars);
	return (1);
}
	/* usleep(1000000/FPS_LIMIT);*/

t_pos	get_player_index(char **map)
{
	t_pos	index;

	index.x = 0;
	index.y = 0;
	while (map[index.y])
	{
		index.x = 0;
		while (map[index.y][index.x])
		{
			if (is_player(map[index.y][index.x]))
				return (index);
			index.x++;
		}
		index.y++;
	}
	return (index);
}

void	get_player_pos(char **map, t_mlx *vars)
{
	t_pos	index;
	index.x = 0;
	index.y = 0;
	while (map[index.y])
	{
		index.x = 0;
		while (map[index.y][index.x])
		{
			if (is_player(map[index.y][index.x]))
			{
				vars->player_data.float_pos.x = 0.5 + index.x;
				vars->player_data.float_pos.y = 0.5 + index.y;
				vars->player_data.index_pos.x = index.x;
				vars->player_data.index_pos.y = index.y;
				vars->player_data.pixel_pos.x = index.x * TILE_SIZE;
				vars->player_data.pixel_pos.y = index.y * TILE_SIZE;
				return ;
			}
			index.x++;
		}
		index.y++;
	}
}

int	check_collision(t_pos index, const t_mlx *vars, char direction)
{
	if (direction == 'N')
		return (vars->map[index.y - 1][index.x] == '1' \
		&& vars->offset.y - PLAYER_SPEED < 0);
	if (direction == 'S')
		return (vars->map[index.y + 1][index.x] == '1' \
	&& vars->offset.y + PLAYER_SPEED > TILE_SIZE - (PLAYER_SIZE));
	if (direction == 'E')
		return (vars->map[index.y][index.x + 1] == '1' \
	&& vars->offset.x + PLAYER_SPEED > TILE_SIZE - (PLAYER_SIZE));
	if (direction == 'W')
		return (vars->map[index.y][index.x - 1] == '1' \
	&& vars->offset.x - PLAYER_SPEED < 0);
	return (0);
}

char	*free_s2_to_join(const char	*s1, char	*s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s2);
	return (temp);
}

void	fps(const t_mlx *vars)
{
	struct timeval	timer;
	struct timeval	total_time;
	char *fps_string;

	gettimeofday(&timer, NULL);
	total_time.tv_usec = timer.tv_usec - vars->time.tv_usec;
	fps_string = ft_itoa(1000000 / total_time.tv_usec);
	fps_string = free_s2_to_join("fps : ", fps_string);
	mlx_string_put(vars->mlx, vars->win, 5, 10, 0x00444444, fps_string);
	free(fps_string);
}

void	map(t_mlx *vars)
{
	if (vars->stats->map_is_create == 0)
	{
		vars->stats->map_is_create = 1;
		vars->stats->old_pos = vars->player_data.pixel_pos;
		draw_map(vars);
		nfree(vars->stats_tile);
		init_mini_map(vars);
		raycast(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->layer[LAYER_MINIMAP].img, WIDTH - vars->layer[LAYER_MINIMAP].w - 100, 100);
	}
	if (vars->stats->old_pos.x != vars->player_data.float_pos.x \
	|| vars->stats->old_pos.y != vars->player_data.float_pos.y || vars->player_data.movement.rotating)
	{
		gettimeofday(&vars->time, NULL);
		vars->stats->old_angle = vars->player_data.movement.rotating;
		vars->stats->old_pos.x = vars->offset.x;
		vars->stats->old_pos.y = vars->offset.y;
		init_mini_map(vars);
		raycast(vars);
		// print_ray_param(&vars->ray);
		mlx_put_image_to_window(vars->mlx, vars->win,
			vars->layer[LAYER_MINIMAP].img, WIDTH_WIN - vars->layer[LAYER_MINIMAP].w - 100, 100);
		fps(vars);
  }
}

void	nfree(void *pointer)
{
	free(pointer);
	pointer = NULL;
}

void	set_starting_direction(t_mlx *vars, const int side)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = vars->ray.dir_x;
	old_plane_x = vars->ray.plane_x;
	vars->ray.dir_x = vars->ray.dir_x * cos(1.5708 * side) - vars->ray.dir_y * sin(1.5708 * side);
	vars->ray.dir_y = old_dir_x * sin(1.5708 * side) + vars->ray.dir_y * cos(1.5708 * side);
	vars->ray.plane_x = vars->ray.plane_x * cos(1.5708 * side) - vars->ray.plane_y * sin(1.5708 * side);
	vars->ray.plane_y = old_plane_x * sin(1.5708 * side) + vars->ray.plane_y * cos(1.5708 * side);
}

void	player_pov_on_start(t_mlx *vars)
{
	char	pov_direction;

	pov_direction = vars->map[vars->player_data.index_pos.y][vars->player_data.index_pos.x];
	if (pov_direction == 'N')
		set_starting_direction(vars, NORTH);
	else if (pov_direction == 'S')
		set_starting_direction(vars, SOUTH);
	else if (pov_direction == 'E')
		set_starting_direction(vars, EAST);
	else if (pov_direction == 'W')
		set_starting_direction(vars, WEST);
}

void	init_vars(t_mlx *vars)
{

	vars->fps = 0;
	vars->offset.x = (TILE_SIZE >> 1) - (PLAYER_SIZE >> 1);
	vars->offset.y = TILE_SIZE >> 1;
	vars->win = mlx_new_window(vars->mlx, WIDTH_WIN, HEIGHT_WIN, "Cub3D");
	vars->layer[LAYER_SCREEN] = new_img(vars, WIDTH_WIN, HEIGHT_WIN);
	vars->layer[LAYER_RAYCAST] = new_img(vars, WIDTH, HEIGHT);
	vars->layer[LAYER_OVERLAY] = new_file_img("texture/Overlay.xpm", vars);
	vars->layer[LAYER_FLOOR] = new_file_img("texture/Ground.xpm", vars);
	get_player_pos(vars->map, vars);
	vars->player_data.movement.rotating = 0;
	vars->ray.dir_x = 1;
	vars->ray.dir_y = 0;
	vars->ray.plane_y = 0.66;
	vars->ray.plane_x = 0;
}

int	main(const int argc, char **argv)
{
	t_info	info;
	t_mlx	vars;

	ft_bzero(&vars, sizeof(t_mlx));
	init_info(&info);
	vars.stats = &info;
	vars.mlx = mlx_init();
	if (argc != 2)
		return (1);
	else
	{
		if (parsing_cube(argv[1], &info, &vars) == 0)
			return (1);
		else
			ft_printf("PARSING ✅\n");
	}
	gettimeofday(&vars.time, NULL);
	vars.map = info.map;
	ft_bzero(&vars.ray, sizeof(vars.ray));
	init_vars(&vars);
	player_pov_on_start(&vars);
	map(&vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop_hook(vars.mlx, tick, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

t_tab_size	char_tab_len(char **tab)
{
	t_tab_size	size;

	size.row = 0;
	size.column = 0;
	while (tab[size.row])
	{
		size.row++;
	}
	while (tab[size.column])
	{
		size.column++;
	}
	return (size);
}

void	print_map(char **map)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (map[i][y])
	{
		while (map[i][y])
		{
			write(1, &map[i][y], 1);
			y++;
		}
		write(1, "\n", 1);
		i++;
		y = 0;
	}
}

int	create_trgb(const int t, const int r, const int g, const int b)
{
	return (((t & ((1 << 8) - 1))) << 24 | \
		(r & ((1 << 8) - 1)) << 16 | \
		(g & ((1 << 8) - 1)) << 8 | \
		(b & ((1 << 8) - 1)));
}
