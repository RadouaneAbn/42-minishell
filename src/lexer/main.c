/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:55:24 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 18:37:24 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	while (true)
	{
		line = readline("\001"BLUE"\002minishell$ \001"RESET"\002");
		if (!line)
		{
			//free_full();
			free_gc();
			break ;
		}
		if (str_blank(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		lexer(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
