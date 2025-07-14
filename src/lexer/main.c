/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:55:24 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 23:44:45 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void sigint_handler(int sig)
{
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
		gc_level_init();
		// printf("[%d]-", get_exit_status());
		line = readline("\001"BLUE"\002minishell$ \001"RESET"\002");
		if (!line)
		{
			// free_full();
			free_level();
			break ;
		}
		if (!str_blank(line))
		{
			add_history(line);
			lexer(line);
		}
		free_level();
	}
	free_level();
	rl_clear_history();
	free_gc();
	// free_full();
	return (0);
}
