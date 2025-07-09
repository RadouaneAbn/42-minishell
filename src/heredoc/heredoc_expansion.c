#include <minishell.h>

void	write_expand_var(char **line, int fd)
{
	char *exit_code;
	char	*key;
	char	*value;

	(*line)++;
	if (**line == '?')
	{
		exit_code = "100";
		ft_putstr_fd(exit_code, fd);
	}
	else
	{
		key = get_key(line);
		value = get_value(key);
		ft_putstr_fd(value, fd);
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
