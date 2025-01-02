/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>                +#+  +:+       +#+  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/09 06:32:34 by lrichaud            ###   ########.fr    */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H
# include "cube3d.h"

void	mouse_move(t_mlx *vars);
void	mouse_bonus(t_mlx *vars);
void	init_bonus(t_mlx *vars);
void	flashlight(t_pos pixel_pos, t_color *color);
int		print_floor_bonus(t_pos *current, t_mlx *vars, t_ray *ray);
t_data	img_cut(t_pos pos, t_mlx *vars, t_pos pos_);

typedef struct s_upscale
{
	t_pos			screen_pos;
	t_pos			rc_pos;
	unsigned int	pixel_color[WIDTH];
	int				nb_pixels;
	int				nb_lines;
	int				nb_px_in_lines;
	float			ratio_h;
	int				i;
	int				j;
	char			*dst;
	int				nb_lines_rc;
	float			ratio_w;
}	t_upscale;

// typedef struct s_mlx
// {
// 	void			*mlx;
// 	void			*win;
// 	t_data			floor;
// 	t_data			layer[10];
// 	t_tile			tile[50];
// 	int				*stats_tile;
// 	t_pos			size_map;
// 	t_posf			offset;
// 	char			**map;
// 	t_player_data	player_data;
// 	struct timeval	time;
// 	struct s_info	*stats;
// 	size_t			fps;
// 	t_ray			ray;
// 	int				light;
// }	t_mlx;

#endif //BONUS_H
