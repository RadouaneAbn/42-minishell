/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:33:41 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:34:45 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	consume(t_token_lst **token_lst)
{
	(*token_lst) = (*token_lst)->next;
}

bool	is_token_word(int operator)
{
	return (operator == WORD);
}

bool	is_output_redirection_operator(int operator)
{
	return (operator == APPEND_OUT || operator == RED_OUT);
}

bool	is_input_redirection_operator(int operator)
{
	return (operator == RED_IN || operator == HERE_DOC);
}

bool	is_redirect_operator(int operator)
{
	return (is_input_redirection_operator(operator)
		|| is_output_redirection_operator(operator));
}
