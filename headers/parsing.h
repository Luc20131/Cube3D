/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:51:48 by sjean             #+#    #+#             */
/*   Updated: 2024/09/26 18:01:50 by sjean            ###   ########.fr       */
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
	char	ceiling[15];
	char	floor[15];
	char	**map;
} t_info;

int get_arg(char *argv, t_info *info);

#endif
