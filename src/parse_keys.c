/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:00:05 by sjean             #+#    #+#             */
/*   Updated: 2024/09/24 15:45:20 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

t_info parse_key(char *argv)
{
	t_info info;

	(void) argv;
	info.map_fp = 1;
	return (info);
}
