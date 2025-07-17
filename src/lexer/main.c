/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:55:24 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 10:48:32 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(130);
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	gc_level_init();
	load_env(env);
	set_exit_status(0);
	while (true)
	{
		line = readline("\001"BLUE"\002minishell$ \001"RESET"\002");
		if (!line)
			break ;
		if (!str_blank(line))
		{
			add_history(line);
			lexer(line);
		}
		free(line);
	}
	free_level();
	rl_clear_history();
	free_gc();
	return (get_exit_status());
}
