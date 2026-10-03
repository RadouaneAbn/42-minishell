/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_last_sibling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:54 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:31:55 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*tree_get_last_sibling(t_tree *tree)
{
	while (tree->sibling)
		tree = tree->sibling;
	return (tree);
}
