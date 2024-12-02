/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:51:48 by sjean             #+#    #+#             */
/*   Updated: 2024/11/03 14:49:04 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <fcntl.h>
# include "cube3d.h"

typedef enum e_key
{
	KEY_NO,
	KEY_SO,
	KEY_EA,
	KEY_WE,
	KEY_F,
	KEY_C
}			t_key;

typedef enum e_statut
{
	E_MALLOC,
	E_FORMAT,
	E_CANT_OPEN,
	E_NO_KEY,
	E_WRONG_KEY,
	E_WRONG_COLOR,
	E_NO_MORE_KEY,
	E_INVALID_MAP,
	E_NO_PLAYER,
	E_HOLE,
	SUCCESS,
	FINISH
}			t_statut;

typedef struct s_stats
{
	struct s_stats	*prev;
	int				dir;
	t_pos			pos;
	struct s_stats	*next;
}				t_stats;

int		get_map(t_info *info);
int		cmp_n_elt(char c, char *cmp);
void	clean_map(char **map, t_stats **stats);
int		parse_map(char **map, t_pos pos);
int		stats_add_back(t_stats **stats, t_pos pos);
int		init_first(t_stats **stats, char **map, t_pos pos);
int		get_dir(t_stats **stats, char **map, t_pos pos);
int		check_holes(t_stats **stats, char **map, t_pos pos);
int		choose_dir(t_stats **stats, char **map, t_pos pos);
int		init_map(t_info *info, t_list *list);
void	free_stats(t_stats **stats);
void	show_map(char **map);
int		init_data_texture(t_info *info, t_mlx *mlx);
int		init_info(t_info *info);

int		check_format(char *map, char *find);
int		check_valid_chr_map(char **map);
int		check_map(t_info *info, t_list **head);
void	error_msg(int error);
int		valid_key(t_info *info);
void	freetab(char **tab);
int		get_arg(char *argv, t_info *info);
int		valid_key(t_info *info);
int		skip_space(char *line);
int		skip_key_word(char *key_v);
int		not_a_word(char c);
int		get_key_value(char *key_v, t_key key, t_info *info);
int		key_finder(char *line);
int		skip_key_word(char *key_v);
int		get_color(char *key_v, t_key key, t_info *info);
int		parsing_cube(char *arg, t_info *info, t_mlx *mlx);
#endif
