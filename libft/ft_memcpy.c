/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:59:41 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 17:34:26 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_char;
	char const	*src_char;

	if ((dest >= src && dest <= src + n - 1)
		|| (src >= dest && src <= dest + n -1))
		return (dest);
	src_char = src;
	dest_char = (char *)dest;
	while (n > 0)
	{
		n--;
		dest_char[n] = src_char[n];
	}
	return (dest);
}
