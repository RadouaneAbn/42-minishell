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
			break ;
		gc_save(line, NULL);
		if (str_blank(line) == false)
		{
			add_history(line);
			lexer(line);
		}
		// free_to_lvl_zero();
		free_level();
	}
	rl_clear_history();
	free_full();
	return (0);
}
