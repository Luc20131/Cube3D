/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:37 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/11 18:05:01 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*src_char;
	char		*dest_char;

	if (src != NULL || dest != NULL)
	{
		src_char = (char *) src;
		dest_char = (char *) dest;
		if (src_char > dest_char)
		{
			i = 0;
			while (++i <= n)
				dest_char[i - 1] = src_char[i - 1];
		}
		else
		{
			while (n > 0)
			{
				n--;
				dest_char[n] = src_char[n];
			}
		}
	}
	return (dest);
}
//#include <stdio.h>
//#include <string.h>

//int main(void)
//{
//	int i = 0;
//	char array[] = "qwerty";
//	char arraytest[] = "patrouille";
//	char *ptr = array;
//	while(i < 6)
//		printf("%c ",array[i++]);
//	printf("%x", *ptr);
//	ptr  = ft_memmove(array, arraytest, 6);
//	// int *testptr = memmove(array, arraytest , 6);
//	
//	printf("\n");
//	i = 0;
//	while(i < 6)
//		printf("%c ",array[i++]);
//	printf("%x", *ptr);
//		
//	//printf("%d", &testptr);
//}
