/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:27:28 by lrichaud          #+#    #+#             */
/*   Updated: 2023/12/01 13:30:07 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	nb_args(const char *str);
static int		type_detector(va_list args_lst, size_t index, const char *str);
int				ft_putnbr_base(long nbr, char *base);
size_t			ft_strlen(const char *s);
int				ft_putstr_size(const char *s, int fd);
int				ft_putptr(unsigned long nbr, char *base);
static int		printer(va_list args_lst, const char *str, int char_printed);

int	ft_printf(const char *str, ...)
{
	va_list	args_lst;
	int		char_printed;

	char_printed = 0;
	va_start(args_lst, str);
	char_printed += printer(args_lst, str, char_printed);
	va_end(args_lst);
	return (char_printed);
}

int	printer(va_list args_lst, const char *str, int char_printed)
{
	long	temp;
	size_t	i;
	size_t	y;

	y = 0;
	i = 0;
	while (nb_args(str) > i)
	{
		while (str[y] != '%')
			char_printed += write(1, &str[y++], 1);
		temp = type_detector(args_lst, y, str);
		if (temp == -1)
			return (-1);
		char_printed += temp;
		y += 2;
		i++;
	}
	while (str[y])
	{
		temp = write(1, &str[y++], 1);
		if (temp == -1)
			return (-1);
		char_printed += temp;
	}
	return (char_printed);
}

static size_t	nb_args(const char *str)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			count++;
		if (str[i] == '%' && str[i + 1] == '%')
			i++;
		i++;
	}
	return (count);
}

static int	type_detector(va_list args_lst, size_t index, const char *str)
{
	char	c;

	if (str[index + 1] == 'd' || str[index + 1] == 'i')
		return (ft_putnbr_base(va_arg(args_lst, int), "0123456789"));
	if (str[index + 1] == 'c')
	{
		c = va_arg(args_lst, int);
		return (write(1, &c, 1));
	}
	if (str[index + 1] == 's')
		return (ft_putstr_size(va_arg(args_lst, const char *), 1));
	if (str[index + 1] == 'p')
		return (ft_putptr(va_arg(args_lst, long), "0123456789abcdef"));
	if (str[index + 1] == 'u')
		return (ft_putnbr_base(va_arg(args_lst, unsigned int), "0123456789"));
	if (str[index + 1] == 'x')
		return (ft_putnbr_base(va_arg(args_lst, unsigned int), \
			"0123456789abcdef"));
	if (str[index + 1] == 'X')
		return (ft_putnbr_base(va_arg(args_lst, unsigned int), \
			"0123456789ABCDEF"));
	if (str[index + 1] == '%')
		return (write(1, "%", 1));
	return (-1);
}
