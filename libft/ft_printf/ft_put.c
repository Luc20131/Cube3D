/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:58:44 by lrichaud          #+#    #+#             */
/*   Updated: 2024/02/13 13:44:07 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

int	ft_putnbr_base(long nbr, char *base)
{
	long	size_base;
	int		char_printed;

	size_base = ft_strlen(base);
	char_printed = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		char_printed += write(1, "-", 1);
		if (char_printed == -1)
			return (-1);
	}
	if (nbr >= size_base)
	{
		char_printed += ft_putnbr_base(nbr / size_base, base);
		if (char_printed == -1)
			return (-1);
	}
	char_printed += write(1, &base[nbr % size_base], 1);
	if (char_printed == -1)
		return (-1);
	return (char_printed);
}

int	ft_putptr(unsigned long nbr, char *base)
{
	size_t	size_base;
	int		char_printed;
	int		temp;

	temp = 0;
	if (nbr == 0)
		return (write(1, "(nil)", 5));
	size_base = ft_strlen(base);
	char_printed = 0;
	char_printed += write(1, "0x", 2);
	if (char_printed == -1)
		return (-1);
	if (nbr >= size_base)
		temp = ft_putnbr_base(nbr / size_base, base);
	if (temp == -1)
		return (-1);
	char_printed += temp;
	temp = write(1, &base[nbr % size_base], 1);
	if (temp == -1)
		return (-1);
	return (char_printed + temp);
}

int	ft_putstr_size(const char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}
