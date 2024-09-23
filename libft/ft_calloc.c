/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 03:28:07 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 17:57:16 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	if (size <= 0 || nmemb <= 0)
		return (malloc(0));
	if (nmemb > __SIZE_MAX__ / size)
		return (NULL);
	i = 0;
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
