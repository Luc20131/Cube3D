/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 04:07:15 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 06:34:22 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	y;
	size_t	result;

	i = 0;
	y = 0;
	while (dest[i] && i < size)
		i++;
	while (src[y])
		y++;
	result = i + y;
	if (size > 0)
	{
		y = 0;
		while (dest[i])
			i++;
		while (src[y] && y + i < size - 1)
		{
			dest[i + y] = src[y];
			y++;
		}
		dest[i + y] = '\0';
	}
	return (result);
}
