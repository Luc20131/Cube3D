/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:32:42 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/22 13:46:22 by sjean            ###   ########.fr       */
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
void	create_pixel(t_mlx *vars, t_pos *origin, t_pos *size, t_data *minimap);
int		*fill_dir_v(int *c, char **map, t_pos pos, t_pos fill);
int		*fill_dir_h(int *c, char **map, t_pos pos, t_pos fill);
int		*l_corner_dir(int *c, t_pos pos, t_mlx g, char **map);
int		*face_corner_v(int *c, t_pos pos, t_mlx g, char **map);
int		*face_corner_h(int *c, t_pos pos, t_mlx g, char **map);
int		*x_dir(int *c, t_pos pos, t_mlx g, t_pos map_size);
void	draw_square(t_data *img, t_pos origin, int size, int color);
void	collision(t_mlx *vars, t_posf pos, t_pos dir, int axe);

// ------------ MINIMAP -------------

int		draw_map(t_mlx *game);
int		map_gen(t_mlx *vars, char **map_tab);
void	start_tiles_init(t_mlx *g);
int		autotile_generator(char **map, t_mlx *g);
t_pos	tile_selector(t_tile tile[49], int *stats);

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
