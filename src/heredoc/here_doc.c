#include <minishell.h>

void	write_expand_var(char **line, int fd)
{
	char *exit_code;
	char	*key;

	(*line)++;
	if (**line == '?')
	{
		exit_code = "100";
		ft_putstr_fd(exit_code, fd);
	}
	else
	{
		key = get_key(line);
		ft_putstr_fd(get_value(key), fd);
	}
}

void	write_expand_line(int fd, char *line)
{
	while (*line)
	{
		if (line[0] == '$' && first_key_ch(line[1]))
			write_expand_var(&line, fd);
		else
			write(fd, line++, 1);
	}
	write(fd, "\n", 1);
}

bool	del_has_quote(char *delimiter)
{
	size_t	index;

	index = 0;
	while (delimiter[index])
	{
		if (char_in_set(delimiter[index], "\"'"))
				return (true);
		index++;
	}
	return (false);
}

bool	del_char_quote(char character, bool reset)
{
	char quote;
	static bool quoted;

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
		if (!del_char_quote(delimiter[index], RESUME))
				len++;
		index++;
	}
	del_char_quote(delimiter[index], REINITIALIZE);
	return (len);
}

char	*get_unquoted_del(char *delimiter)
{
	size_t	index;
	size_t	len;
	char	*unquoted_delimiter;

	index = 0;
	len = get_unquoted_del_size(delimiter);
	unquoted_delimiter  = malloc((len + 1) * sizeof(char));
	while (*delimiter)
	{
		if (!del_char_quote(*delimiter, RESUME))
		{
			unquoted_delimiter[index] = *delimiter;
			index++;
		}
		delimiter++;
	}
	del_char_quote(delimiter[index], REINITIALIZE);
	return (unquoted_delimiter);
}

char	*here_doc(char *delimiter)
{
	int	fd;
	char	*addr;
	char	*file_name;
	char 	*line;
	bool	should_expand;	
	char	*unquoted_delimiter;

	should_expand = !del_has_quote(delimiter);
	addr = utoa((size_t)&fd);
	unquoted_delimiter = get_unquoted_del(delimiter);
	//file_name = ft_strjoin("/tmp/file-minishell--", addr);

	file_name = "./file.txt";
	fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0700);
	while (true)
	{
		line = readline("> ");	
		if (line == NULL)
			printf("bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s')", unquoted_delimiter);
		if (strmatch(line, unquoted_delimiter))
			break ;
		add_history(line);
		if (should_expand)
			write_expand_line(fd, line);
		else
			ft_putstr_fd(line, fd);
		free(line);
	}
	printf("%s\n", file_name);
	return (file_name);
}
