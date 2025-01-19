/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:51:48 by sjean             #+#    #+#             */
/*   Updated: 2025/01/19 09:56:33 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <fcntl.h>

typedef enum e_key
{
	KEY_NO,
	KEY_SO,
	KEY_WE,
	KEY_EA,
	KEY_F,
	KEY_C,
	SKIP
}			t_key;

typedef enum e_statut
{
	E_MALLOC,
	E_FORMAT,
	E_CANT_OPEN,
	E_NO_KEY,
	E_WRONG_KEY,
	E_WRONG_COLOR,
	E_NO_COLOR,
	E_NO_MORE_KEY,
	E_INVALID_MAP,
	E_INVALID_CHARACTER,
	E_INVALID_LINE,
	E_NO_PLAYER,
	E_TO_MANY_PLAYER,
	E_HOLE,
	E_NOT_XPM,
	E_DUPLICATE_KEY,
	SUCCESS,
	FINISH
}			t_statut;

#endif
