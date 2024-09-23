/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_splited.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:17:14 by lrichaud          #+#    #+#             */
/*   Updated: 2024/03/26 16:26:09 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_splited(char **strs_array)
{
	size_t	i;

	i = 0;
	while (strs_array[i])
		free(strs_array[i++]);
	free(strs_array);
}
