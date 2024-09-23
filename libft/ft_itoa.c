/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:05:08 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/13 17:42:44 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_int_size(int n);
static char		*set_nbr_to_str(size_t i, int n, char *n_str);

char	*ft_itoa(int n)
{
	size_t	size;
	char	*n_str;
	size_t	i;

	size = ft_int_size(n);
	n_str = malloc((size + 1) * sizeof(char));
	if (n_str == NULL)
		return (NULL);
	n_str[size] = '\0';
	if (n == 0)
	{
		n_str[0] = '0';
		return (n_str);
	}
	if (n == -2147483648)
	{
		n /= 10;
		n_str[size - 1] = '8';
		size--;
	}
	i = size - 1;
	n_str = set_nbr_to_str(i, n, n_str);
	return (n_str);
}

static size_t	ft_int_size(int n)
{
	size_t	size;

	size = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*set_nbr_to_str(size_t i, int n, char *n_str)
{
	if (n < 0)
		n *= -1;
	while (i > 0)
	{
		n_str[i--] = n % 10 + '0';
		n /= 10;
	}
	if (n > 0)
		n_str[i] = n + '0';
	else
		n_str[i] = '-';
	return (n_str);
}
