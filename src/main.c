/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:52:12 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/07 00:21:34 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_player(const char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void	my_destroy_img(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

void	exit_game(t_mlx *vars)
{
	int	i;

	i = 0;
	mlx_do_key_autorepeaton(vars->mlx);
	while (vars->map[i])
		nfree(vars->map[i++]);
	nfree(vars->map);
	my_destroy_img(vars->mlx, vars->layer[LAYER_SCREEN].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_OVERLAY].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_MINIMAP].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_MAP].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_RAYCAST].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_FLOOR].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_MONITOR].img);
	my_destroy_img(vars->mlx, vars->layer[LAYER_ACHANGER].img);
	my_destroy_img(vars->mlx, vars->stats->img_texture[0].img);
	my_destroy_img(vars->mlx, vars->stats->img_texture[1].img);
	my_destroy_img(vars->mlx, vars->stats->img_texture[2].img);
	my_destroy_img(vars->mlx, vars->stats->img_texture[3].img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	nfree(vars->mlx);
	exit(1);
}

int	tick(t_mlx *vars)
{
	if (vars->player_data.movement.forward)
	{
		vars->player_data.float_pos.x += (PLAYER_SPEED * vars->ray.dir.x);
		vars->player_data.float_pos.y += (PLAYER_SPEED * vars->ray.dir.y);
	}
	else if (vars->player_data.movement.backward)
	{
		vars->player_data.float_pos.x -= (PLAYER_SPEED * vars->ray.dir.x);
		vars->player_data.float_pos.y -= (PLAYER_SPEED * vars->ray.dir.y);
	}
	else if (vars->player_data.movement.right)
	{
		vars->player_data.float_pos.x -= (PLAYER_SPEED * vars->ray.dir.y);
		vars->player_data.float_pos.y += (PLAYER_SPEED * vars->ray.dir.x);
	}
	else if (vars->player_data.movement.left)
	{
		vars->player_data.float_pos.x += (PLAYER_SPEED * vars->ray.dir.y);
		vars->player_data.float_pos.y -= (PLAYER_SPEED * vars->ray.dir.x);
	}
	player_pos_update(vars, vars->map);
	map(vars);
	return (1);
}

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

void	nfree(void *pointer)
{
	free(pointer);
	pointer = NULL;
}

void	set_starting_direction(t_mlx *vars, const int side)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = vars->ray.dir.x;
	old_plane_x = vars->ray.plane.x;
	vars->ray.dir.x = vars->ray.dir.x * cos(1.5708 * side) \
		- vars->ray.dir.y * sin(1.5708 * side);
	vars->ray.dir.y = old_dir_x * sin(1.5708 * side) \
		+ vars->ray.dir.y * cos(1.5708 * side);
	vars->ray.plane.x = vars->ray.plane.x * cos(1.5708 * side) \
		- vars->ray.plane.y * sin(1.5708 * side);
	vars->ray.plane.y = old_plane_x * sin(1.5708 * side) \
		+ vars->ray.plane.y * cos(1.5708 * side);
}

void	player_pov_on_start(t_mlx *vars)
{
	const t_pos	pos = vars->player_data.index_pos;
	const char	pov_direction = vars->map[pos.y][pos.x];

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
	vars->offset.x = (TILE_SIZE >> 1) - (PLAYER_SIZE >> 1);
	vars->offset.y = TILE_SIZE >> 1;
	vars->win = mlx_new_window(vars->mlx, WIDTH_WIN, HEIGHT_WIN, "Cub3D");
	vars->layer[LAYER_SCREEN] = new_img(vars, WIDTH_WIN, HEIGHT_WIN);
	vars->layer[LAYER_RAYCAST] = new_img(vars, WIDTH, HEIGHT);
	vars->layer[LAYER_OVERLAY] = new_file_img("texture/Overlay.xpm", vars);
	vars->layer[LAYER_FLOOR] = new_file_img("texture/stars.xpm", vars);
	vars->layer[LAYER_MONITOR] = new_file_img("texture/monitoring.xpm", vars);
	vars->layer[LAYER_ACHANGER] = new_file_img("texture/SusMap.xpm", vars);
	get_player_pos(vars->map, vars);
	vars->player_data.movement.rotating = 0;
	vars->ray.dir.x = 1;
	vars->ray.dir.y = 0;
	vars->ray.plane.y = 0.66;
	vars->ray.plane.x = 0;
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
	if (parsing_cube(argv[1], &info) == 0)
		return (1);
	ft_printf("PARSING ✅\n");
	init_data_texture(&info, &vars);
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

int	create_trgb(const int t, const int r, const int g, const int b)
{
	return (((t & ((1 << 8) - 1))) << 24 | \
		(r & ((1 << 8) - 1)) << 16 | \
		(g & ((1 << 8) - 1)) << 8 | \
		(b & ((1 << 8) - 1)));
}
