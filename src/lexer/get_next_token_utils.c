/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:53:55 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:53:56 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_operator(int index)
{
	static char	*fully[9];

	if (fully[0] == NULL)
	{
		fully[AND] = "&&";
		fully[OR] = "||";
		fully[HERE_DOC] = "<<";
		fully[APPEND_OUT] = ">>";
		fully[RED_IN] = "<";
		fully[RED_OUT] = ">";
		fully[PIPE] = "|";
		fully[L_PAREN] = "(";
		fully[R_PAREN] = ")";
	}
	return (fully[index]);
}

t_token_type	get_operator_type(char *line, size_t *position)
{
	size_t	len;
	char	*token_value;
	t_token_type	index;

	index = 0;
	while (index < 9)
	{
		token_value = get_operator(index);
		len = ft_strlen(token_value);
		if (strnmatch(line + *position, token_value, len))
			break ;
		index++;
	}
	return (index);
}

bool	token_is_operator(char *line, size_t position)
{
	size_t	len;
	char	*token_value;
	int		index;

	index = 0;
	while (index < 9)
	{
		token_value = get_operator(index);
		len = ft_strlen(token_value);
		if (strnmatch(line + position, token_value, len))
			return (true);
		index++;
	}
	return (false);
}

void	check_unclosed_quote(bool unclosed_quote)
{
	if (unclosed_quote)
	{
		ft_putendl_fd("minishell: unclosed quote", 2);
		*syntax_err_value() = true;
		//free and set a var inside a function
	}
}
