/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:49:05 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 20:18:00 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	put_heredoc_line(bool should_expand, char *line, int fd)
{
	if (should_expand)
		write_expand_line(fd, line);
	else
		ft_putendl_fd(line, fd);
}

static int	*get_heredoc_fd(void)
{
	static int fd;

	return (&fd);	
}

void	sig_heredoc_handler(int sig)
{
	int	fd;

	fd = *get_heredoc_fd();
	(void)sig;
	close(fd);
	free_full();
	exit (130);
}


void	run_heredoc(t_expand_info expand_info)
{
	char	*line;
	pid_t	pid;
	int	fd;

	fd = *get_heredoc_fd();
	pid = fork();
	if (pid == 0)
	{
		while (true)
		{
			line = readline("> ");
			if (line == NULL)
			{
				ft_putstr_fd("minishell: warning: ", 2);
				ft_putstr_fd("here-document delimited by end-of-file (wanted`", 2);
				ft_putstr_fd(expand_info.unquoted_delimiter, 2);
				ft_putstr_fd("'", 2);
				break ;
			}
			if (strmatch(line, expand_info.unquoted_delimiter))
				break ;
			//add_history(line);
			put_heredoc_line(expand_info.should_expand, line, fd);
			free(line);
		}
		free_full();
		close(fd);
		exit(0);
	}
	else
	{
		wait(NULL);
	}
}

char	*heredoc(char *delimiter)
{
	int				fd;
	char			*addr;
	char			*file_name;
	t_expand_info	expand_info;

	addr = utoa((size_t)(&fd));
	expand_info = (t_expand_info)heredoc_expand_info(delimiter);
	file_name = ft_strjoin("/tmp/file-minishell--", addr);
	fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0700);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		return (NULL);
	}
	*get_heredoc_fd() = fd;
	run_heredoc(expand_info);
	close(fd);
	return (file_name);
}
