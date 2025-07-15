/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:04:20 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/15 17:40:55 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void create_new_env(void)
{
	char *s;
	char *tmp;
	char *tmp_2;

	pre_export("OLDPWD");
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("minishell: getcwd");
		return ;
	}
	s = ft_strjoin("PWD=", tmp);
	gc_local_free(tmp);
	pre_export(s);
	gc_local_free(s);
}

void	load_env(char **env)
{
	int	i;

	gc_level_init();
	i = 0;
	if (env[0] != NULL)
	{
		while (env[i])
		{
			pre_export(env[i]);
			i++;
		}
	}
	else
		create_new_env();
	free_level();
}
