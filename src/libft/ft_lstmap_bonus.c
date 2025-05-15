/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:30:54 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/30 22:30:56 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	lstmap_healper(t_list **head, t_list **tail, t_list *node)
{
	if (*head == NULL)
	{
		*head = node;
		*tail = node;
	}
	else
	{
		(*tail)->next = node;
		*tail = (*tail)->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*tail;
	t_list	*new_node;
	void	*tmp;

	head = NULL;
	tail = NULL;
	tmp = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		new_node = ft_lstnew(tmp);
		if (new_node == NULL)
		{
			del(tmp);
			ft_lstclear(&head, del);
			return (NULL);
		}
		lstmap_healper(&head, &tail, new_node);
		lst = lst->next;
	}
	return (head);
}
