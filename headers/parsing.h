/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:51:48 by sjean             #+#    #+#             */
/*   Updated: 2024/10/15 17:51:41 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <linux/limits.h>
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

typedef struct s_info
{
	int		map_fd;
	char	texture_path[4][PATH_MAX];
	int		ceiling[3];
	int		floor[3];
	int		texture_valid[4];
	t_pos	player;
	char	**map;

}	t_info;

typedef struct s_stats
{
	struct s_stats	*prev;
	int 			dir;
	t_pos			pos;
	struct s_stats	*next;
 }				t_stats;


int	get_map(t_info *info);
int	cmp_n_elt(char c, char *cmp);

int	get_arg(char *argv, t_info *info);
int valid_key(t_info *info);
int	skip_space(char *line);
int	skip_key_word(char *key_v);
int	not_a_word(char c);
int	get_key_value(char *key_v, t_key key, t_info *info);
int	key_finder(char *line);
int	skip_key_word(char *key_v);
int	get_color(char *key_v, t_key key, t_info *info);
int	parsing_cube(char *arg);
#endif
