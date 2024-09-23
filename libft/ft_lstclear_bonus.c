/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 05:20:35 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/21 10:26:33 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr_lst;
	t_list	*temp;

	ptr_lst = *lst;
	if (lst == NULL || *lst == 0)
		return ;
	while (ptr_lst->next)
	{
		del(ptr_lst->content);
		temp = ptr_lst->next;
		free(ptr_lst);
		ptr_lst = temp;
	}
	del(ptr_lst->content);
	free(ptr_lst);
	*lst = NULL;
}
