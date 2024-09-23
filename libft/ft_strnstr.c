/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 03:43:40 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 06:32:41 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr_str;
	size_t	i;
	size_t	y;
	int		diff;

	ptr_str = NULL;
	diff = 0;
	i = 0;
	if (little[0] == '\0' || little == big)
		return ((char *) big);
	while (big[i] && i < len)
	{
		if (i < len && big[i] == little[0])
		{
			y = -1;
			while (little[++y] && big[i + y] && y + i < len)
				diff = big[i + y] - little[y];
			if (little[y] == '\0' && diff == 0 && y + i <= len)
				return ((char *) big + i);
		}
		i++;
	}
	return (ptr_str);
}
