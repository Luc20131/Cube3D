/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:46:09 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/15 07:56:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>
#include <stdio.h>

int	get_t(const int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(const int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(const int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(const int trgb)
{
	return (trgb & 0xFF);
}


