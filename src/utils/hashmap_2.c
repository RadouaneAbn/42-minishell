/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:04:13 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 18:57:17 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_from_map(t_map *map, char *key)
{
	int		idx;
	t_node	*current_node;
	t_node	*prev;

	idx = hash(key);
	current_node = map->map[idx];
	prev = NULL;
	while (current_node)
	{
		if (ft_strcmp(current_node->key, key) == 0)
			break ;
		prev = current_node;
		current_node = current_node->next;
	}
	if (current_node == map->map[idx])
		map->map[idx] = current_node->next;
	else
		prev->next = current_node->next;
}

t_map	*get_map(void)
{
	t_info	*info;

	info = get_info();
	if (info == NULL)
		return (NULL);
	return (&(info->exports));
}
