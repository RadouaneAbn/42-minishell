/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_uid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:38:12 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 16:02:32 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*create_new_id(char *id, char *buf)
{
	unsigned short int	*int_buf;
	int					int_index;
	int					i;

	int_buf = (unsigned short int *)buf;
	int_index = 0;
	i = 7;
	while (id[i])
	{
		if (id[i] == '*')
			id[i] = 'a' + (int_buf[int_index++] % 26);
		i++;
	}
	return (id);
}

char	*id(void)
{
	char	*pattern;
	int		fd;
	char	*id;
	char	buf[READ_SIZE];

	pattern = "/tmp/heredoc-****-********";
	id = ft_strdup(pattern);
	if (!id)
		return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(id);
		return (NULL);
	}
	if (read(fd, buf, READ_SIZE) <= 0)
	{
		close(fd);
		free(id);
		return (NULL);
	}
	close(fd);
	return (create_new_id(id, buf));
}
