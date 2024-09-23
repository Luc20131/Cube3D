/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:36:56 by lrichaud          #+#    #+#             */
/*   Updated: 2024/09/23 12:12:41 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_settings
{
	int	fov;
	float	move_speed;
}	t_settings;

typedef struct s_player
{
	t_pos	pos;
	float	orientation;
}	t_player;
