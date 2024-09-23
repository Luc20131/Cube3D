/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:55:32 by lrichaud          #+#    #+#             */
/*   Updated: 2023/11/22 10:18:51 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_node_content;

	new_lst = NULL;
	if (f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		new_node_content = f(lst->content);
		new_node = ft_lstnew(new_node_content);
		if (new_node == NULL)
		{
			ft_lstclear(&new_lst, del);
			del(new_node_content);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
