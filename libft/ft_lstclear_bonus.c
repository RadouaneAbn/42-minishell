/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:47:33 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/13 11:46:09 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (lst == 0)
		return ;
	if (*lst == 0 || del == 0)
		return ;
	while ((*lst) != 0)
	{
		del((*lst)->content);
		ptr = (*lst)->next;
		free((*lst));
		*lst = ptr;
	}
}
