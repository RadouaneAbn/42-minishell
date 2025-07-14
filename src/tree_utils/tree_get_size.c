/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:17 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:31:18 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tree_get_size(t_tree *list)
{
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list != NULL)
	{
		list = list->next;
		len++;
	}
	return (len);
}
