/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_add_sibling_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:38 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:30:38 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	tree_add_sibling_back(t_tree **head, t_tree *new)
{
	t_tree	*last_sibling;

	if (*head == NULL)
		(*head) = new;
	else
	{
		last_sibling = tree_get_last_sibling(*head);
		last_sibling->sibling = new;
	}
}
