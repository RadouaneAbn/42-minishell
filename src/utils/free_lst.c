/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:25:35 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:25:36 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_list(t_list **list)
{
	t_list	*ptr;

	if (list == NULL)
		return ;
	while ((*list) != NULL)
	{
		gc_global_free((*list)->content);
		ptr = (*list)->next;
		gc_global_free((*list));
		*list = ptr;
	}
}
