/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:27 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 19:33:34 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_export_args(char *arg)
{
	int		idx;
	char	**arr;

	if (arg == NULL)
		return (NULL);
	arr = gc_malloc(sizeof(char *) * 3);
	if (arr == NULL)
		return (NULL);
	idx = ft_index_of(arg, '=');
	if (idx != -1)
	{
		arr[0] = ft_substr(arg, 0, idx);
		gc_save(arr[0], NULL);
		arr[1] = ft_substr(arg, idx + 1, ft_strlen(arg) - idx);
		gc_save(arr[1], NULL);
		arr[2] = NULL;
	}
	else
	{
		arr[0] = ft_strdup(arg);
		gc_save(arr[0], NULL);
		arr[1] = NULL;
		arr[2] = NULL;
	}
	return (arr);
}

int	key_isvalid(char *key)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[i]) == true)
		return (false);
	while (key[i])
	{
		if (key[i] == '-')
			return (false);
		if (key[i] != '_' && ft_isalnum(key[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

void	print_export_error(char *key, char *value)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	if (value)
	{
		ft_putstr_fd("=", 2);
		ft_putstr_fd(value, 2);
	}
	ft_putendl_fd("': not a valid identifier", 2);
}

int	pre_export(char *exported)
{
	char	**args;
	int		status;

	args = split_export_args(exported);
	if (key_isvalid(args[0]) == FALSE)
	{
		print_export_error(args[0], args[1]);
		return (EXIT_FAILURE);
	}
	status = export(args[0], args[1]);
	return (status);
}

int	export(char *key, char *value)
{
	t_map	*map;
	int		status;

	map = get_map();
	if (map == NULL)
		return (EXIT_FAILURE);
	status = add_to_map(map, key, value);
	if (status != EXIT_FAILURE)
		map->size++;
	return (status);
}
