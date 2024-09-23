/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:58:15 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 10:14:07 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*substract_str(const char *s, char *n_str, size_t start, size_t l);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;

	if (s == NULL)
		return (NULL);
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (ft_strlen(s) - start < len)
		len--;
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	else
	{
		new_str = (char *) malloc((len + 1) * sizeof(char));
		if (new_str == NULL)
			return (NULL);
		new_str = substract_str(s, new_str, start, len);
		if (new_str == NULL)
			return (NULL);
	}
	return (new_str);
}

static char	*substract_str(const char *s, char *n_str, size_t start, size_t l)
{
	size_t	i;
	size_t	y;

	y = 0;
	i = 0;
	while (i < start)
		i++;
	while (y < l && s[i + y])
	{
		n_str[y] = s[i + y];
		y++;
	}
	n_str[y] = '\0';
	return (n_str);
}

// int main(int argc, char const *argv[])
// {
// 	char *str = "0123456789";
//     char *s = ft_substr(str, 9, 10);
// 	printf("%s",s);
// 	return 0;
// }
