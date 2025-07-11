/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:45:10 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/11 02:10:04 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*node_to_string(t_node *node)
{
	char	*s;
	int		t_size;

	t_size = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	s = gc_malloc(t_size * sizeof(char));
	s[0] = 0;
	ft_strlcat(s, node->key, t_size);
	ft_strlcat(s, "=", t_size);
	ft_strlcat(s, node->value, t_size);
	return (s);
}

char	**build_env(void)
{
	t_map	*map;
	char	**env;
	t_node	*node;
	int		i;

	map = get_map();
	node = map->ordered_list;
	env = gc_malloc((map->size + 1) * sizeof(char *));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (node)
	{
		if (node->value)
			env[i++] = node_to_string(node);
		node = node->ordered_next;
	}
	env[i] = NULL;
	return (env);
}

bool	has_exec_perm(char *path)
{
	return (access(path, X_OK) == 0);
}
