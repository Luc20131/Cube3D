/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/15 07:56:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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

void	init_vars(t_mlx *vars)
{
	vars->offset.x = (TILE_SIZE >> 1) - (PLAYER_SIZE >> 1);
	vars->offset.y = TILE_SIZE >> 1;
	vars->win = mlx_new_window(vars->mlx, WIDTH_WIN, HEIGHT_WIN, "Cub3D");
	vars->layer[SCREEN] = new_img(vars, WIDTH_WIN, HEIGHT_WIN);
	vars->layer[RAYCAST] = new_img(vars, WIDTH, HEIGHT);
	vars->layer[OVERLAY] = new_file_img("texture/Overlay.xpm", vars);
	vars->layer[FLOOR] = new_file_img("texture/Ground.xpm", vars);
	vars->layer[MONITOR] = new_file_img("texture/monitoring.xpm", vars);
	vars->layer[TILES] = new_file_img("texture/SusMap.xpm", vars);
	vars->anim[0] = new_file_img("texture/animation/Flashlight1.xpm", vars);
	vars->anim[1] = new_file_img("texture/animation/Flashlight2.xpm", vars);
	vars->anim[2] = new_file_img("texture/animation/Flashlight3.xpm", vars);
	vars->anim[3] = new_file_img("texture/animation/Flashlight4.xpm", vars);
	get_player_pos(vars->map, vars);
	vars->player_data.movement.rotating = 0;
	vars->player_data.is_moving = 0;
	vars->ray.dir.x = 1;
	vars->ray.dir.y = 0;
	vars->ray.plane.y = 0.66;
	vars->ray.plane.x = 0;
	vars->size_map = size_map(vars->map);
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

void	player_pos_update(t_mlx *vars, char **map)
{
	static t_pos	old_pos = {0, 0};
	t_posf			posf_player;

	posf_player = vars->player_data.float_pos;
	if (posf_player.x >= vars->size_map.x || posf_player.y >= vars->size_map.y
		|| posf_player.x < 0 || posf_player.y < 0)
		return ;
	if (old_pos.x == 0 && old_pos.y == 0)
	{
		old_pos.x = (int)posf_player.x;
		old_pos.y = (int)posf_player.y;
	}
	if (map[old_pos.y][old_pos.x] != '1'
		&& map[(int)posf_player.y][(int)posf_player.x] != '1')
	{
		map[old_pos.y][old_pos.x] = '0';
		map[(int)posf_player.y][(int)posf_player.x] = 'N';
		old_pos.x = (int)posf_player.x;
		old_pos.y = (int)posf_player.y;
		vars->player_data.pixel_pos.x = TILE_SIZE * posf_player.x;
		vars->player_data.pixel_pos.y = TILE_SIZE * posf_player.y;
	}
}
