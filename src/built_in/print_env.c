/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:29 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/15 17:02:22 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_env(void)
{
	t_map	*map;
	t_node	*node;

	map = get_map();
	if (map == NULL)
		return (1);
	node = map->ordered_list;
	while (node)
	{
		if (node->value)
		{
			ft_putstr_fd(node->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(node->value, 1);
		}
		node = node->ordered_next;
	}
	return (0);
}

int	print_exports(void)
{
	t_map	*map;
	t_node	*node;

	map = get_map();
	if (map == NULL)
		return (EXIT_FAILURE);
	node = map->ordered_list;
	while (node)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(node->key, 1);
		if (node->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(node->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		node = node->ordered_next;
	}
	return (EXIT_SUCCESS);
}
