/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 02:14:28 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 13:01:16 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*char_ptr;

	char_ptr = NULL ;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
		{
			char_ptr = (char *) s + i;
		}
		i++;
	}
	if (s[i] == (char) c)
	{
		char_ptr = (char *) s + i;
	}
	return (char_ptr);
}
