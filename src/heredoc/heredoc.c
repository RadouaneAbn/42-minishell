/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:49:05 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 10:55:51 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	*get_heredoc_fd(void)
{
	static int	fd;

	return (&fd);
}

static void	sig_heredoc_handler(int sig)
{
	int	fd;

	fd = *get_heredoc_fd();
	(void)sig;
	close(fd);
	write(1, "\n", 1);
	clean_exit(130);
}

bool	run_heredoc(t_expand_info expand_info)
{
	pid_t	pid;
	int		fd;
	int		status;

	fd = *get_heredoc_fd();
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_heredoc_handler);
		fill_heredoc(expand_info, fd);
	}
	else
	{
		wait(&status);
		signal(SIGINT, sigint_handler);
		if (WEXITSTATUS(status) == 130)
			return (true);
	}
	return (false);
}

char	*heredoc(char *delimiter)
{
	int				fd;
	char			*file_name;
	t_expand_info	expand_info;
	bool			is_signaled;

	expand_info = (t_expand_info)heredoc_expand_info(delimiter);
	file_name = id();
	fd = open(file_name, O_TRUNC | O_CREAT | O_RDWR, 0700);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		return (NULL);
	}
	*get_heredoc_fd() = fd;
	is_signaled = run_heredoc(expand_info);
	close(fd);
	if (is_signaled)
		return (NULL);
	return (file_name);
}
