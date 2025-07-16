/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:34:52 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 12:32:48 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*tree_get_io_redirect_list(t_token_lst	**token_lst)
{
	t_tree	*io_files_list;
	t_tree	*io_files;

	io_files_list = NULL;
	while ((*token_lst))
	{
		if (is_redirect_operator((*token_lst)->token.type))
		{
			io_files = tree_get_io_redirect(token_lst);
			if (!io_files)
			{
				free_tree(&io_files_list);
				return (NULL);
			}
			tree_add_back(&io_files_list, io_files);
		}
		else
			break ;
	}
	return (io_files_list);
}

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
	t_tree	*io_redirect_list;
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

bool	tree_set_command(t_token_lst **token_lst, t_tree **command)
{
	t_tree	*subshell;
	t_tree	*simple_command;

	*command = tree_create_new(T_COMMAND, NULL);
	if ((*token_lst)->token.type == L_PAREN)
	{
		subshell = parse_subshell(token_lst);
		if (subshell == NULL)
			return (free_tree(command), false);
		tree_add_back(command, subshell);
	}
	else
	{
		simple_command = parse_simple_command(token_lst);
		if (simple_command == NULL)
			return (free_tree(command), false);
		tree_add_back(command, simple_command);
	}
	return (true);
}

t_tree	*tree_get_command(t_token_lst **token_lst)
{
	t_tree	*command;
	bool	check_err;

	command = NULL;
	if ((*token_lst) && (*token_lst)->token.type != AND
		&& (*token_lst)->token.type != OR
		&& (*token_lst)->token.type != PIPE)
	{
		check_err = tree_set_command(token_lst, &command);
		if (!check_err)
			return (NULL);
	}
	return (command);
}
