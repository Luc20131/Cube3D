/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:10:14 by sjean             #+#    #+#             */
/*   Updated: 2024/11/03 18:55:40 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"

void	tile_assembler(t_tile *tile, int nb, t_pos pos)
{
	tile->pos = pos;
	tile->dir = nb;
}

void	end_tiles_init(t_tile *t, t_mlx *g)
{
	tile_assembler(&t[39], 155, (t_pos){5, 5});
	tile_assembler(&t[40], 440, (t_pos){4, 6});
	tile_assembler(&t[41], 248, (t_pos){4, 7});
	tile_assembler(&t[42], 62, (t_pos){5, 6});
	tile_assembler(&t[43], 59, (t_pos){5, 7});
	tile_assembler(&t[44], 443, (t_pos){4, 8});
	tile_assembler(&t[45], 254, (t_pos){5, 8});
	tile_assembler(&t[46], 7, (t_pos){2, 0});
	tile_assembler(&t[47], 0, (t_pos){2, 1});
	tile_assembler(&t[48], 186, (t_pos){5, 1});
	tile_assembler(&t[49], 499, (t_pos){4, 4});
	mlx_destroy_image(g->mlx, g->tilemap.img);
}

void	middle_tiles_init(t_tile *t, t_mlx *g)
{
	tile_assembler(&t[19], 219, (t_pos){2, 3});
	tile_assembler(&t[20], 504, (t_pos){3, 2});
	tile_assembler(&t[21], 63, (t_pos){3, 3});
	tile_assembler(&t[22], 191, (t_pos){2, 4});
	tile_assembler(&t[23], 506, (t_pos){2, 5});
	tile_assembler(&t[24], 251, (t_pos){3, 4});
	tile_assembler(&t[25], 446, (t_pos){3, 5});
	tile_assembler(&t[26], 442, (t_pos){2, 6});
	tile_assembler(&t[27], 250, (t_pos){2, 7});
	tile_assembler(&t[28], 190, (t_pos){3, 6});
	tile_assembler(&t[29], 187, (t_pos){3, 7});
	tile_assembler(&t[30], 56, (t_pos){2, 8});
	tile_assembler(&t[31], 146, (t_pos){3, 8});
	tile_assembler(&t[32], 184, (t_pos){4, 2});
	tile_assembler(&t[33], 154, (t_pos){4, 3});
	tile_assembler(&t[34], 58, (t_pos){5, 2});
	tile_assembler(&t[35], 178, (t_pos){5, 3});
	tile_assembler(&t[36], 434, (t_pos){4, 4});
	tile_assembler(&t[37], 218, (t_pos){4, 5});
	tile_assembler(&t[38], 182, (t_pos){5, 4});
	end_tiles_init(t, g);
}

void	start_tiles_init(t_mlx *g)
{
	g->tilemap = new_file_img("texture/SusMap.xpm", g);
	tile_assembler(&g->tile[0], 48, (t_pos){0, 0});
	tile_assembler(&g->tile[1], 18, (t_pos){0, 1});
	tile_assembler(&g->tile[2], 144, (t_pos){1, 0});
	tile_assembler(&g->tile[3], 24, (t_pos){1, 1});
	tile_assembler(&g->tile[4], 176, (t_pos){0, 2});
	tile_assembler(&g->tile[5], 152, (t_pos){0, 3});
	tile_assembler(&g->tile[6], 50, (t_pos){1, 2});
	tile_assembler(&g->tile[7], 26, (t_pos){1, 3});
	tile_assembler(&g->tile[8], 255, (t_pos){0, 4});
	tile_assembler(&g->tile[9], 447, (t_pos){0, 5});
	tile_assembler(&g->tile[10], 507, (t_pos){1, 4});
	tile_assembler(&g->tile[11], 510, (t_pos){1, 5});
	tile_assembler(&g->tile[12], 432, (t_pos){0, 6});
	tile_assembler(&g->tile[13], 216, (t_pos){0, 7});
	tile_assembler(&g->tile[14], 54, (t_pos){1, 6});
	tile_assembler(&g->tile[15], 27, (t_pos){1, 7});
	tile_assembler(&g->tile[16], 511, (t_pos){0, 8});
	tile_assembler(&g->tile[17], 16, (t_pos){1, 8});
	tile_assembler(&g->tile[18], 438, (t_pos){2, 2});
	middle_tiles_init(g->tile, g);
}
