#include <minishell.h>

char	*here_doc(char *delimiter)
{
	int	fd;
	char	*addr;
	char	*file_name;
	char 	*line;

	 addr = utoa((size_t)&fd);
	//file_name = ft_strjoin("/tmp/file-minishell--", addr);
	
	file_name = "./file.txt";
	fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0700);
	//printf("%d\n", fd);
	while (true)
	{
		line = readline("> ");	
		if (line == NULL || strmatch(line, delimiter))
			break ;
		//add_history(line);
		//write(fd, line, strlen(line));
		//write(fd, "\n", 1);
		ft_putendl_fd(line, fd);
		free(line);
	}
	printf("%s\n", file_name);
	return (file_name);
}
