#include <minishell.h>

void	put_heredoc_line(bool should_expand, char *line, int fd)
{
	if (should_expand)
		write_expand_line(fd, line);
	else
		ft_putendl_fd(line, fd);
}

void	run_heredoc(t_expand_info expand_info, int fd)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s')",
				expand_info.unquoted_delimiter);
			break ;
		}
		if (strmatch(line, expand_info.unquoted_delimiter))
			break ;
		//add_history(line);
		put_heredoc_line(expand_info.should_expand, line, fd);
		free(line);
	}
}

char	*heredoc(char *delimiter)
{
	int		fd;
	char	*addr;
	char	*file_name;
	t_expand_info	expand_info;

	addr = utoa((size_t)(&fd));
	expand_info = (t_expand_info)heredoc_expand_info(delimiter);
	//file_name = ft_strjoin("/tmp/file-minishell--", addr);
	file_name = "./file.txt";
	fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0700);
	run_heredoc(expand_info, fd);
	return (file_name);
}
