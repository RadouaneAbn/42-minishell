/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:48:17 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/15 20:01:54 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr;

	if (lst == 0 || new == 0)
		return ;
	ptr = ft_lstlast(*lst);
	if (ptr == NULL)
	{
		*lst = new;
		return ;
	}
	ptr->next = new;
	new->next = 0;
}
