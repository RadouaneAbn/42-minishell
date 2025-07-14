/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:32 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:30:33 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tree_add_back(t_tree **head, t_tree *new)
{
	t_tree	*last_node;

	if (*head == NULL)
		(*head) = new;
	else
	{
		last_node = tree_get_last(*head);
		last_node->next = new;
	}
}
