/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:45 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:30:46 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*tree_create_new(int data_type, void *parameter)
{
	t_tree	*new;

	new = gc_malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->data_type = data_type;
	new->data = parameter;
	new->next = NULL;
	new->sibling = NULL;
	return (new);
}
