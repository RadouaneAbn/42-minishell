/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:50:27 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/12 15:53:02 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lexer(char *line)
{
	t_token		token;
	t_token_lst	*new_node;
	t_token_lst	*token_lst;
	t_tree	*tree;

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
	{
		free_token_list(&token_lst);
		*syntax_err_value() = false;
		return ;
	}
	tree = parser(token_lst);
	if (*syntax_err_value())
	{
		free_token_list(&token_lst);
		*syntax_err_value() = false;
		return ;
	}
	free_token_list(&token_lst);
	//print_tree(tree, 0);
	expand_simple_command_lst(tree->next->next->next);
	free_tree(tree);
}
