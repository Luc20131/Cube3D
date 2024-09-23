/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:01:36 by lrichaud          #+#    #+#             */
/*   Updated: 2024/08/25 21:56:31 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"

typedef struct s_vector
{
	t_pos	origin;
	int		delta_x;
	int		delta_y;
};

t_data	img_for_vectors_init(t_mlx *vars, int	size)
{
	t_data	map;
	t_pos	carac_pos;

	carac_pos.x = 200;
	carac_pos.y = 250;
	map = new_img(vars, 1500);

}
