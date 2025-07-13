/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:25 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:37:26 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_env(char *key)
{
	t_map	*map;
	t_node	*node;

	map = get_map();
	if (map == NULL)
		return (NULL);
	node = find_in_map(map, key);
	if (node)
		return (node->value);
	return ("");
}
