/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:29 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:37:30 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_env(int fd)
{
	t_map	*map;
	t_node	*node;

	map = get_map();
	if (map == NULL)
		return (1);
	if (fd == -1)
		fd = STDOUT_FILENO;
	node = map->ordered_list;
	while (node)
	{
		if (node->value)
		{
			ft_putstr_fd(node->key, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(node->value, fd);
		}
		node = node->ordered_next;
	}
	return (0);
}

int	print_exports(int fd)
{
	t_map	*map;
	t_node	*node;

	map = get_map();
	if (map == NULL)
		return (EXIT_FAILURE);
	if (fd == -1)
		fd = STDOUT_FILENO;
	node = map->ordered_list;
	while (node)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(node->key, fd);
		if (node->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(node->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		node = node->ordered_next;
	}
	return (EXIT_SUCCESS);
}
