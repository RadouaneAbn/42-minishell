#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <readline/readline.h>

void	here_doc(char *delimiter)
{
	int	fd;
	char	*addr;
	char	*file_name;
	char 	*line;

	 addr = utoa((size_t)&fd);
	file_name = ft_strjoin("/tmp/file-minishell--", addr);
	
	fd = open(file_name, O_CREAT);
	while (true)
	{
		line = readline("> ");	
		if (line == NULL || strmatch(line, delimiter))
			break ;
		add_history(line);
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", file_name);
}

int	main(void)
{
	here_doc("hey");
	return (0);
}
