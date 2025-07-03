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
