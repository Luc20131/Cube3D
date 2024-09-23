/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:06:24 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/15 08:32:53 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int		test_set(const char c, char const *set);
static size_t			trimmed_str_size(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	size = trimmed_str_size(s1, set);
	new_str = malloc(size + 1 * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	new_str[size] = '\0';
	while (s1[i] && test_set(s1[i], set))
		i++;
	while (s1[i] && j < size)
		new_str[j++] = s1[i++];
	return (new_str);
}

static size_t	trimmed_str_size(char const *s1, char const *set)
{
	int		i;
	size_t	size;

	i = 0;
	size = ft_strlen(s1);
	while (s1[i] && test_set(s1[i], set))
		i++;
	size -= i;
	i = ft_strlen(s1) - 1;
	while (i > 0 && size > 0 && test_set(s1[i--], set))
		size--;
	return (size);
}

static unsigned int	test_set(const char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}
