/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:51:48 by sjean             #+#    #+#             */
/*   Updated: 2024/10/02 17:29:53 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <linux/limits.h>
# include <fcntl.h>

typedef enum e_key
{
	KEY_NO,
	KEY_SO,
	KEY_EA,
	KEY_WE,
	KEY_F,
	KEY_C
}			t_key;

typedef enum e_error
{
	E_MALLOC,
	E_NO_KEY,
	E_WRONG_KEY,
	E_WRONG_COLOR
}			t_error;

typedef struct s_info
{
	int		map_fd;
	char	texture_path[4][PATH_MAX];
	int		ceiling[3];
	int		floor[3];
	char	**map;
} t_info;

int get_arg(char *argv, t_info *info);
int	skip_space(char *line);
int	get_key_value(char *key_v, t_key key, t_info *info);
int	key_finder(char *line);
int skip_key_word(char *key_v);
int	get_color(char *key_v, t_key key, t_info *info);
int parsing_cube(char *arg);
#endif
