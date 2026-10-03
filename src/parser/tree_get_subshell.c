/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:18:46 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 10:18:46 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	tree_set_subshell_redirect(t_token_lst	**token_lst, t_tree **subshell)
{
	t_tree	*io_redirect_list;

	io_redirect_list = tree_get_io_redirect_list(token_lst);
	if (!io_redirect_list)
		return (false);
	tree_add_sibling_back(subshell, io_redirect_list);
	return (true);
}

void	throw_unclosed_brace_err(void)
{
	*syntax_err_value() = true;
	ft_putendl_fd("minishell: syntax error: unclosed  bracket", 2);
}

bool	tree_set_subshell(t_token_lst	**token_lst, t_tree **subshell)
{
	t_tree	*compound_command;
	bool	check_err;

	consume(token_lst);
	compound_command = tree_get_compound_command(token_lst);
	if (compound_command == NULL)
		return (false);
	if ((*token_lst) && (*token_lst)->token.type == R_PAREN)
		consume(token_lst);
	else
	{
		if (!(*token_lst))
			throw_unclosed_brace_err();
		return (free_tree(&compound_command), false);
	}
	*subshell = tree_create_new(T_SUBSHELL, NULL);
	if ((*token_lst) && is_redirect_operator((*token_lst)->token.type))
	{
		check_err = tree_set_subshell_redirect(token_lst, subshell);
		if (!check_err)
			return (free_tree(&compound_command), free_tree(subshell), NULL);
	}
	tree_add_back(subshell, compound_command);
	return (true);
}

t_tree	*parse_subshell(t_token_lst	**token_lst)
{
	t_tree	*subshell;
	bool	check_err;

	subshell = NULL;
	if ((*token_lst) && (*token_lst)->next)
	{
		check_err = tree_set_subshell(token_lst, &subshell);
		if (!check_err)
			return (NULL);
	}
	return (subshell);
}
