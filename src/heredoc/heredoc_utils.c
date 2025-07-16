/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:42:16 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 21:42:18 by hsacr            ###   ########.fr       */
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

void	fill_heredoc(t_expand_info expand_info, int fd)
{
	char	*line;

	while (true)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putstr_fd("minishell: warning: \
					here-document delimited by end-of-file (wanted`", 2);
			ft_putstr_fd(expand_info.unquoted_delimiter, 2);
			ft_putstr_fd("'\n", 2);
			break ;
		}
		if (strmatch(line, expand_info.unquoted_delimiter))
			break ;
		put_heredoc_line(expand_info.should_expand, line, fd);
		free(line);
	}
	close(fd);
	clean_exit(0);
}
