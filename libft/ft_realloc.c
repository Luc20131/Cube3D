/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:34:04 by lrichaud          #+#    #+#             */
/*   Updated: 2024/03/27 18:48:43 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t nb_elem, size_t size)
{
	void	*new_array;

	if (size <= 0 || nb_elem <= 0)
	{
		free(ptr);
		return (malloc(0));
	}
	if (nb_elem > __SIZE_MAX__ / size)
	{
		free(ptr);
		return (NULL);
	}
	new_array = ft_calloc(nb_elem, size);
	if (!new_array)
		return (NULL);
	ft_memcpy(new_array, ptr, nb_elem * size);
	free(ptr);
	return (new_array);
}
