/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:17:28 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 10:17:29 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UTILS_H
# define TREE_UTILS_H

void	free_tree(t_tree **tree);
void	tree_add_back(t_tree **head, t_tree *new);
void	tree_add_sibling_back(t_tree **head, t_tree *new);
t_tree	*tree_create_new(int data_type, void *parameter);
t_tree	*tree_get_last(t_tree *tree);
t_tree	*tree_get_last_sibling(t_tree *tree);
int		tree_get_size(t_tree *list);
#endif
