/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:43:58 by lrichaud          #+#    #+#             */
/*   Updated: 2024/12/07 13:17:15 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <linux/limits.h>
# include "types.h"
# include "parsing.h"
# include <sys/time.h>
# include <bits/types/struct_timeval.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdio.h>
# include <sys/types.h>


t_tab_size		char_tab_len(char **tab);
void			wall(t_data *img, float distance);

// ------------ INIT ---------------

void			init_vars(t_mlx *vars);
void			init_value_for_cast(t_ray *ray, t_mlx *vars, t_pos *origin);
int				init_mini_map(t_mlx *vars);
void			player_pov_on_start(t_mlx *vars);

// ------------ PLAYER -------------

int				is_player(char c);
void			get_player_pos(char **map, t_mlx *vars);
t_pos			get_player_index(char **map);
void			player_pos_update(t_mlx *vars, char **map);
void			rotate_right(t_mlx *vars);
void			rotate_left(t_mlx *vars);

// ------------ KEYBOARD -------------

int				key_hook( int keycode, t_mlx *vars);
int				key_released(int keycode, t_mlx *vars);

// ------------ MINIMAP -------------

t_pos			size_map(char **map);
void			draw_map(t_mlx *game);
int				map_gen(t_mlx *vars, char **map_tab);
void			start_tiles_init(t_mlx *g);
void			autotile_generator(char **map, t_mlx *g);

// ------------ RAYCAST -------------

int				raycast(t_mlx *vars);

// ------------ IMG UTILS -------------

t_data			new_img(t_mlx *vars, unsigned int width, unsigned int height);
t_data			new_file_img(char *path, t_mlx *window);
unsigned int	get_pixel_img(t_data *img, int x, int y);
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
void			get_darker_color(float coef, t_color *color);
float			init_pixel_tex_y(t_pos *current, float step);
int				init_pixel_tex_x(t_ray *ray, t_mlx *vars);
int				*fill_dir_v(int *c, char **map, t_pos pos, t_pos fill);
int				*fill_dir_h(int *c, char **map, t_pos pos, t_pos fill);
int				*l_corner_dir(int *c, t_pos pos, t_mlx g, char **map);
int				*face_corner_v(int *c, t_pos pos, t_mlx g, char **map);
int				*face_corner_h(int *c, t_pos pos, t_mlx g, char **map);
int				*x_dir(int *c, t_pos pos, t_mlx g, t_pos map_size);
void			draw_square(t_data *img, t_pos origin, int size, int color);
// void			my_mlx_pixel_put(const t_data *data, const int x, const int y, const int color);
void			upscale_rc_to_screen(t_mlx *vars, t_data *screen);
void			my_destroy_img(void *mlx, void *img);

// ------------ UTILS -------------

int				print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top);
int				print_floor(t_pos *current, t_mlx *vars, t_ray *ray);
int				print_wall(t_pos *current, t_mlx *vars, \
				t_pos *end, t_data *img);

t_data			select_texture(t_data img[4], t_mlx *vars);
int				vertical_raycast(t_mlx *vars, t_pos *end);
void			fps(const t_mlx *vars);
void			nfree(void *pointer);
void			print_ray_param(t_ray *ray);
void			print_map(char *map[]);
void			exit_game(t_mlx *vars);
int				tick(t_mlx *vars);
void			fps(const t_mlx *vars);

#endif
