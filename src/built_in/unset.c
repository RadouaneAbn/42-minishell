/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:35 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:37:36 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_env_variable(t_map *map, char *key)
{
	t_node	*wanted_node;

	wanted_node = find_in_map(map, key);
	if (wanted_node == NULL)
		return ;
	remove_from_ordered_list(map, key);
	remove_from_map(map, key);
	free(wanted_node->key);
	free(wanted_node->value);
	free(wanted_node);
	map->size--;
}

int	unset(char *key)
{
	t_map	*map;

	map = get_map();
	if (map == NULL)
		return (1);
	remove_env_variable(map, key);
	return (0);
}
