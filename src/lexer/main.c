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
		//rl_redisplay();
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!str_blank(line))
		{
			lexer(line);
			//expand(line);
			//printf("%zu\n", expand_str_len(line));
		}
		free(line);
	}
	rl_clear_history();
	return (0);
}
