/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:04:20 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 19:33:36 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	load_env(char **env)
{
	int	i;

	gc_level_init();
	i = 0;
	while (env[i])
	{
		pre_export(env[i]);
		i++;
	}
	free_level();
}
