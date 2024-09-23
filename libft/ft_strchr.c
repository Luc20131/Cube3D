/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:20:08 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 12:59:30 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*char_ptr;

	i = 0;
	while (s[i] != (unsigned char) c && s[i] != '\0')
	{
		i++;
	}
	if (s[i] == (unsigned char) c)
	{
		char_ptr = (char *) s + i;
	}
	else
		char_ptr = 0;
	return (char_ptr);
}

//int main(void)
//{
//	char *test = "cyberpunk";
//	char *ptr = ft_strchr(test,'b');
//	if (ptr != NULL)
//		printf("%c",*ptr);
//}
