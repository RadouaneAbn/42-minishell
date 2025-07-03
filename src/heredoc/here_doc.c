#include <minishell.h>

bool	is_removable_quote(char character, bool reset)
{
	char			quote;
	static bool		quoted;

	if (!reset)
	{
		if (char_in_set(character, "\"'") && !quoted)
			quote = character;
		if (char_in_set(character, "\"'") && character == quote)
		{
			quoted = !quoted;
			return (true);
		}
	}
	else
		quoted = false;
	return (false);
}

size_t	get_unquoted_del_size(char *delimiter)
{
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	while (delimiter[index])
	{
		if (!is_removable_quote(delimiter[index], RESUME))
			len++;
		index++;
	}
	is_removable_quote(0, REINITIALIZE);
	return (len);
}

t_expand_info	heredoc_expand_info(char *delimiter)
{
	size_t					index;
	size_t					len;
	t_expand_info					expand_info;

	expand_info.should_expand = true;
	index = 0;
	len = get_unquoted_del_size(delimiter);
	expand_info.unquoted_delimiter = malloc((len + 1) * sizeof(char));
	while (*delimiter)
	{
		if (!is_removable_quote(*delimiter, RESUME))
		{
			expand_info.unquoted_delimiter[index] = *delimiter;
			index++;
		}
		else
			expand_info.should_expand = false;
		delimiter++;
	}
	expand_info.unquoted_delimiter[index] = '\0';
	is_removable_quote(0, REINITIALIZE);
	return (expand_info);
}

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
			printf("bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s')", expand_info.unquoted_delimiter);
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

	addr = utoa((size_t)&fd);
	expand_info = (t_expand_info)heredoc_expand_info(delimiter);
	//file_name = ft_strjoin("/tmp/file-minishell--", addr);
	file_name = "./file.txt";
	fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0700);
	run_heredoc(expand_info, fd);
	return (file_name);
}
