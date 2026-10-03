/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:53:22 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:53:41 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_operator_token(t_token *token, char *line, size_t *position)
{
	size_t	len;
	int		index;
	int		is_operator;
	char	*token_value;

	is_operator = token_is_operator(line, *position);
	if (is_operator)
	{
		index = get_operator_type(line, position);
		token_value = get_operator(index);
		len = ft_strlen(token_value);
		token->type = index;
		token->lexeme = ft_strdup(token_value);
		*position += len;
		return ;
	}
}

void	set_word_token(t_token *token, char *line, size_t *position)
{
	bool	quoted;
	size_t	start;

	quoted = false;
	start = *position;
	while (((!quoted && !(token_is_operator(line, *position)
					|| is_space(line[*position])))
			|| (quoted)) && line[*position] != '\0')
	{
		if (is_removable_quote(line[*position], RESUME))
			quoted = !quoted;
		(*position)++;
	}
	check_unclosed_quote(quoted);
	if (start != *position)
	{
		token->lexeme = ft_substr(line, start, *position - start);
		token->type = WORD;
	}
	is_removable_quote(0, REINITIALIZE);
}

void	get_token(t_token *token, char *line, size_t *position)
{
	while (is_space(line[*position]))
		*position += 1;
	if (line[*position])
	{
		if (token_is_operator(line, *position))
			set_operator_token(token, line, position);
		else
			set_word_token(token, line, position);
	}
}

void	get_next_token(t_token *token, char *line)
{
	static size_t	index;

	get_token(token, line, &index);
	if (token->lexeme == NULL)
		index = 0;
}
