/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:45:52 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 06:33:45 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*char_ptr;
	const unsigned char	*str_ptr;

	char_ptr = NULL;
	if (n > 0)
	{
		str_ptr = s;
		i = 0;
		while (str_ptr[i] != (unsigned char) c && i < n - 1)
		{
			i++;
		}
		if (str_ptr[i] == (unsigned char) c)
		{
			char_ptr = (unsigned char *) s + i;
		}
	}
	return (char_ptr);
}
