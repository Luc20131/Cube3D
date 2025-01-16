/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/16 14:48:54 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H
# include "types.h"
# include <sys/time.h>

void	mouse_move(t_mlx *vars);
void	mouse_bonus(t_mlx *vars);
void	init_bonus(t_mlx *vars);
t_data	*get_img_frame(t_mlx *vars);
int		print_floor_bonus(t_pos *current, t_mlx *vars, t_ray *ray);
t_data	img_cut(t_pos pos, t_mlx *vars, t_pos pos_);
void	upscale_rc_to_screen(t_data *raycast, t_data *screen);
int		vertical_raycast(t_mlx *vars, t_pos *end);
void	flashlight(t_pos pixel_pos, t_color *color);
int		print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top);
int		print_floor(t_pos *current, t_mlx *vars);
void	fps(const t_mlx *vars);
void	collision(t_mlx *vars, t_posf pos, t_pos dir, int axe);

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

#endif //BONUS_H
