/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 19:44:48 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 10:20:51 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 1;
	if (lst == 0)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
