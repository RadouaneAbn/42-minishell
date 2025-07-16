/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:22 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 10:54:02 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tree(t_tree **tree)
{
	t_tree	*tmp;

	while (*tree)
	{
		gc_global_free((*tree)->data);
		free_tree(&(*tree)->next);
		tmp = *tree;
		*tree = (*tree)->sibling;
		gc_global_free(tmp);
	}
}
