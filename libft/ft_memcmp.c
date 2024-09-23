/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 03:37:45 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 05:34:04 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s1_ptr;
	char	*s2_ptr;
	int		value_returned;

	s1_ptr = (char *) s1;
	s2_ptr = (char *) s2;
	i = 0;
	if (n < 1)
		return (0);
	while (s1_ptr[i] == s2_ptr[i] && i < n - 1)
		i++;
	value_returned = (unsigned char) s1_ptr[i] - (unsigned char) s2_ptr[i];
	return (value_returned);
}
