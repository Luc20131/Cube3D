/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 22:52:12 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/14 17:26:54 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "parsing.h"

void	delete_all_img(t_mlx *vars)
{
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
	my_destroy_img(vars->mlx, vars->anim[0].img);
	my_destroy_img(vars->mlx, vars->anim[1].img);
	my_destroy_img(vars->mlx, vars->anim[2].img);
	my_destroy_img(vars->mlx, vars->anim[3].img);
}

void	exit_game(t_mlx *vars)
{
	int	i;

	i = 0;
	mlx_do_key_autorepeaton(vars->mlx);
	while (vars->map[i])
		nfree(vars->map[i++]);
	nfree(vars->map);
	delete_all_img(vars);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	nfree(vars->mlx);
	exit(1);
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

int	main(const int argc, char **argv)
{
	t_info	info;
	t_mlx	vars;

	ft_bzero(&vars, sizeof(t_mlx));
	init_info(&info);
	vars.stats = &info;
	if (argc != 2)
		return (1);
	if (parsing_cube(argv[1], &info) == 0)
		return (1);
	ft_printf("PARSING ✅\n");
	vars.map = info.map;
	vars.mlx = mlx_init();
	if (init_data_texture(&info, &vars) == E_MALLOC)
		return (exit_game(&vars), 1);
	init_vars(&vars);
	player_pov_on_start(&vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_hook, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_released, &vars);
	mlx_loop_hook(vars.mlx, tick, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	mlx_loop(vars.mlx);
	return (0);
}
