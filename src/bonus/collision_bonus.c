/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:19:56 by sjean             #+#    #+#             */
/*   Updated: 2025/01/21 02:35:18 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "bonus.h"
#define HITBOX 0.02

int	can_move_v(char **map, t_posf pos, int dir, float ray_dir)
{
	if (map[(int)(pos.y + HITBOX + (PLAYER_SPEED * ray_dir) * dir)]
	[(int)(pos.x + HITBOX)] != '1' \
	&& map[(int)(pos.y + HITBOX + (PLAYER_SPEED * ray_dir) * dir)]
	[(int)(pos.x - HITBOX)] != '1'\
	&& map[(int)(pos.y - HITBOX + (PLAYER_SPEED * ray_dir) * dir)]
	[(int)(pos.x + HITBOX)] != '1'\
	&& map[(int)(pos.y - HITBOX + (PLAYER_SPEED * ray_dir) * dir)]
	[(int)(pos.x - HITBOX)] != '1')
		return (1);
	return (0);
}

int	can_move_h(char **map, t_posf pos, int dir, float ray_dir)
{
	if (map[(int)(pos.y + HITBOX)]
	[(int)(pos.x + HITBOX + (PLAYER_SPEED * ray_dir) * dir)] != '1' \
	&& map[(int)(pos.y + HITBOX)]
	[(int)(pos.x - HITBOX + (PLAYER_SPEED * ray_dir) * dir)] != '1' \
	&& map[(int)(pos.y - HITBOX)]
	[(int)(pos.x + HITBOX + (PLAYER_SPEED * ray_dir) * dir)] != '1' \
	&& map[(int)(pos.y - HITBOX)]
	[(int)(pos.x - HITBOX + (PLAYER_SPEED * ray_dir) * dir)] != '1')
		return (1);
	return (0);
}

void	collision(t_mlx *vars, t_posf pos, t_pos dir, int axe)
{
	if (axe == 0)
	{
		if (can_move_h(vars->map, pos, dir.x, vars->ray.dir.x))
			vars->player_data.float_pos.x += \
			(PLAYER_SPEED * vars->ray.dir.x) * dir.x;
		if (can_move_v(vars->map, pos, dir.y, vars->ray.dir.y))
			vars->player_data.float_pos.y += \
			(PLAYER_SPEED * vars->ray.dir.y) * dir.y;
	}
	else if (axe == 1)
	{
		if (can_move_h(vars->map, pos, dir.x, vars->ray.dir.y))
			vars->player_data.float_pos.x += \
			(PLAYER_SPEED * vars->ray.dir.y) * dir.x;
		if (can_move_v(vars->map, pos, dir.y, vars->ray.dir.x))
			vars->player_data.float_pos.y += \
			(PLAYER_SPEED * vars->ray.dir.x) * dir.y;
	}
}
