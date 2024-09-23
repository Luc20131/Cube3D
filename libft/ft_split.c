/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:55:52 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 12:58:57 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*strs_free(char **s);
static int	str_counter(const char *s, char c);
static int	str_size(const char *s, char c, int start);
static char	**set_split_array(int nb_str, const char *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**strs_array;

	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return (set_split_array(0, s, c));
	strs_array = set_split_array(str_counter(s, c), s, c);
	if (strs_array == NULL)
		return (NULL);
	return (strs_array);
}

static char	**set_split_array(int nb_str, const char *s, char c)
{
	char	**strs_array;
	size_t	i;
	size_t	j;
	size_t	size;

	size = 0;
	i = 0;
	j = 0;
	strs_array = ft_calloc((nb_str + 1), sizeof(char *));
	if (strs_array == NULL)
		return (NULL);
	strs_array[nb_str] = NULL;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			return (strs_array);
		size = str_size(s, c, j);
		strs_array[i] = ft_substr(s, j, size);
		if (strs_array[i++] == NULL)
			return (strs_free(strs_array));
		j += size;
	}
	return (strs_array);
}

static int	str_counter(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (c == '\0' && s[0])
		return (1);
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == c)
			count++;
		i++;
	}
	if (s[i - 1] != c && s[i] == '\0')
		count++;
	return (count);
}

static int	str_size(const char *s, char c, int start)
{
	size_t	i;

	if (!s[0])
		return (0);
	i = start;
	while (s[i] && s[i] != c)
		i++;
	return (i - start);
}

static void	*strs_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (NULL);
}

// int main(int argc, char const *argv[])
// {
// 	int i =0;
// 	char *strrrrrr = NULL;
// 	char **str =   ft_split(strrrrrr,' ');
// 	if (str == NULL)
// 	{
// 		write(1,"OK",2);
// 	}
// 	// while (str[i])
// 	// 	ft_putendl_fd(str[i++], 1);
// 	// strs_free(str);
// 	return 0;
// }
