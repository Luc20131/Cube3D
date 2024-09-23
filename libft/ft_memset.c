/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:23:27 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/08 00:47:27 by lrichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*string;

	string = s;
	while (n > 0)
	{
		*string = c;
		string++;
		n--;
	}
	return (s);
}

//#include <stdio.h>
//#include <string.h>
//
//int main(void)
//{
//	int i = 0;
//	int array[6] = { 'q', 'w', 'e', 'r', 't' ,'y'};
//	int arraytest[6] = { 'q', 'w', 'e', 'r', 't' ,'y'};
//	
//	int *ptr  = ft_memset(array, 48, 6);
//	int *testptr = memset(arraytest, 48 , 6);
//	while(i < 6)
//		printf("%c ",array[i++]);
//	printf("%d", &ptr);
//	printf("\n");
//	i = 0;
//	while(i < 6)
//		printf("%c ",arraytest[i++]);
//		
//	printf("%d", &testptr);
//}
