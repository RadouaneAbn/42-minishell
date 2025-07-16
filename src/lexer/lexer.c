/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:50:27 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 21:30:30 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	syntax_err_signal_setup(int exit_status, bool *func(void))
{
	*func() = false;
	set_exit_status(exit_status);
	free_level();
}

bool	check_err_and_heredoc_signal()
{
	if (*heredoc_signaled())
		return (syntax_err_signal_setup(130, heredoc_signaled), true);
	if (*syntax_err_value())
		return (syntax_err_signal_setup(2, syntax_err_value), true);
	return (false);
}

void	lexer(char *line)
{
	t_token		token;
	t_token_lst	*new_node;
	t_token_lst	*token_lst;
	t_tree		*tree;

	gc_level_init();
	token_lst = NULL;
	while (true)
	{
		token.lexeme = NULL;
		get_next_token(&token, line);
		if (token.lexeme == NULL)
			break ;
		new_node = token_lstnew(token);
		token_lstadd_back(&token_lst, new_node);
	}
	if (*syntax_err_value())
		return (syntax_err_signal_setup(2, syntax_err_value));
	tree = parser(token_lst);
	if (check_err_and_heredoc_signal())
		return ;
	free_token_list(&token_lst);
	execute_tree(tree);
	free_level();
}
