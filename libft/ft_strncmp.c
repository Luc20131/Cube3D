/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:28:09 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/16 23:06:42 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	int			value_returned;

	i = 0;
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && s2[i] && i < n - 1)
		i++;
	value_returned = (unsigned char) s1[i] - (unsigned char) s2[i];
	return (value_returned);
}
