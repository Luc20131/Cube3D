/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:16:40 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 12:59:55 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_assembly(char const *s1, char const *s2);

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_joined;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	else
		str_joined = str_assembly(s1, s2);
	return (str_joined);
}

static char	*str_assembly(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*str_joined;
	size_t	y;

	i = 0;
	y = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	str_joined = malloc((size + 1) * sizeof(char));
	if (str_joined == NULL)
		return (NULL);
	while (i < size && i < ft_strlen(s1))
	{
		str_joined[i] = s1[i];
		i++;
	}
	while (i + y < size)
	{
		str_joined[i + y] = s2[y];
		y++;
	}
	str_joined[size] = '\0';
	return (str_joined);
}
