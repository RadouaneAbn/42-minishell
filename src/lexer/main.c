#include <minishell.h>
#include <signal.h>

int	main(int argc, char *argv[], char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	while (true)
	{
		line = readline(BLUE"minishell$ "RESET);
		rl_redisplay();
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		lexer(line);
		//expand(line);
		printf("\n");
		free(line);
	}
	rl_clear_history();
	return (0);
}
