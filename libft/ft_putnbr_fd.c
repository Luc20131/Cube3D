/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 03:59:55 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 03:09:43 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		digit = n % 10 + '0';
		write(fd, &digit, 1);
	}
}
