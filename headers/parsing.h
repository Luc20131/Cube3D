/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjean <sjean@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:51:48 by sjean             #+#    #+#             */
/*   Updated: 2024/09/25 16:22:11 by sjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <linux/limits.h>
# include <fcntl.h>

typedef struct s_info
{
	int		map_fd;
	char	texture_path[4][PATH_MAX];
	char	Ceiling[3];
	char	floor[3];
	char	**map;
} t_info;

int get_arg(char *argv, t_info info);

#endif