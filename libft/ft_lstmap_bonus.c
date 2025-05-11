/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:12:20 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/11 09:52:55 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*more(void (*del)(void *), void *content)
{
	del(content);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*ptr;
	void	*tmp;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	tmp = f(lst->content);
	head = ft_lstnew(tmp);
	if (head == 0)
		return (more(del, tmp));
	ptr = head;
	while (lst->next)
	{
		ft_lstadd_back(&ptr, ft_lstnew(f(lst->content)));
		if (ptr == 0)
		{
			ft_lstclear(&head, del);
			return (0);
		}
		ptr = ptr->next;
		lst = lst->next;
	}
	return (head);
}
