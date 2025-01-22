
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:43:58 by lrichaud          #+#    #+#             */
/*   Updated: 2025/01/19 09:44:31 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef BONUS
#  include "bonus.h"
# else
#  define WIDTH WIDTH_WIN
#  define HEIGHT HEIGHT_WIN
#  include "types.h"
# endif
# include "parsing.h"

t_tab_size		char_tab_len(char **tab);
void			wall(t_data *img, float distance);

// ------------ INIT ---------------

void			init_vars(t_mlx *vars);
void			init_value_for_cast(t_ray *ray, t_mlx *vars, t_pos *origin);
int				init_mini_map(t_mlx *vars);
void			player_pov_on_start(t_mlx *vars);

// ------------ PLAYER -------------

int				is_player(char c);
t_pos			get_player_index(char **map);
void			player_pos_update(t_mlx *vars, char **map);
void			rotate_right(t_mlx *vars);
void			rotate_left(t_mlx *vars);

// ------------ KEYBOARD -------------

int				key_hook( int keycode, t_mlx *vars);
int				key_released(int keycode, t_mlx *vars);

// ------------ RAYCAST -------------

void			raycast(t_mlx *vars);
void			stop_casting(t_ray *ray, char **map, t_pos size_map);

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
void			my_destroy_img(void *mlx, void *img);
void			put_pixel_img(t_data *img, int x, int y, int color);
void			put_data_to_img(t_data *dst, t_data src, int x, int y);
void			put_img_to_img(t_data *src, t_data *dst);

// ------------ UTILS -------------

void			print_wall(t_pos *current, t_mlx *vars,
					t_pos *end, t_data *img);
t_data			select_texture(t_data img[4], t_mlx *vars);
int				exit_game(t_mlx *vars);
int				tick(t_mlx *vars);
void			nfree(void *pointer);
int				print_ceilling(t_pos *current, t_mlx *vars, t_pos *wall_top);
int				print_floor(t_pos *current, t_mlx *vars);
t_pos			size_map(char **map);

// ------------ PARSING -------------

int				get_map(t_info *info);
int				cmp_n_elt(char c, char *cmp);
int				parse_map(char **map);
int				stats_add_back(t_stats **stats, t_pos pos);
int				init_first(t_stats **stats, char **map, t_pos pos);
int				get_dir(t_stats **stats, char **map, t_pos pos);
int				choose_dir(t_stats **stats, char **map, t_pos pos);
int				init_map(t_info *info, t_list *list);
void			free_stats(t_stats **stats);
void			show_map(char **map);
int				init_data_texture(t_info *info, t_mlx *mlx);
int				init_info(t_info *info);
int				check_format(char *map, char *find);
int				check_valid_chr_map(char **map);
int				check_map(t_info *info, t_list **head);
void			error_msg(int error, char *content);
void			freetab(char **tab);
int				get_arg(t_info *info);
int				valid_key(t_info *info, int print);
int				skip_space(char *line);
int				skip_key_word(char *key_v);
int				not_a_word(char c);
int				get_key_value(char *key_v, t_key key, t_info *info);
int				key_finder(char *line);
int				skip_key_word(char *key_v);
int				get_color(char *key_v, t_key key, t_info *info);
int				parsing_cube(char *arg, t_info *info);
void			map(t_mlx *vars);

#endif
