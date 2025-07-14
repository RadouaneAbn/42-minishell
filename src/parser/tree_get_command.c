/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:34:52 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:34:53 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*tree_get_io_redirect_list(t_token_lst	**token_lst)
{
	t_tree	*io_files;

	io_files = NULL;
	while ((*token_lst))
	{
		if (is_redirect_operator((*token_lst)->token.type))
		{
			tree_add_back(&io_files, tree_get_io_redirect(token_lst));
		}
		else
			break ;
	}
	return (io_files);
}

t_tree	*parse_subshell(t_token_lst	**token_lst)
{
	t_tree	*compound_command;
	t_tree	*io_redirect_list;
	t_tree	*subshell;

	subshell = NULL;
	if ((*token_lst) && (*token_lst)->next)
	{
		consume(token_lst);
		compound_command = tree_get_compound_command(token_lst);
		if (compound_command == NULL)
			return (NULL);
		if ((*token_lst) && (*token_lst)->token.type == R_PAREN)
			consume(token_lst);
		else
		{
			if (!(*token_lst))
			{
				*syntax_err_value() = true;
				ft_putendl_fd("minishell: syntax error: unclosed  bracket", 2);
			}
			free_tree(compound_command);
			return (NULL);
		}
		subshell = tree_create_new(T_SUBSHELL, NULL);
		if ((*token_lst))
		{
			io_redirect_list = tree_get_io_redirect_list(token_lst);
			tree_add_sibling_back(&subshell, io_redirect_list);
		}
		tree_add_back(&subshell, compound_command);
	}
	return (subshell);
}

t_tree	*tree_get_command(t_token_lst **token_lst)
{
	t_tree	*command;
	t_tree	*subshell;
	t_tree	*simple_command;

	command = NULL;
	if ((*token_lst) && (*token_lst)->token.type != AND
		&& (*token_lst)->token.type != OR
		&& (*token_lst)->token.type != PIPE)
	{
		command = tree_create_new(T_COMMAND, NULL);
		if ((*token_lst)->token.type == L_PAREN)
		{
			subshell = parse_subshell(token_lst);
			if (subshell == NULL)
				return (free_tree(command), NULL);
			tree_add_back(&command, subshell);
		}
		else
		{
			simple_command = parse_simple_command(token_lst);
			if (simple_command == NULL)
				return (free_tree(command), NULL);
			tree_add_back(&command, simple_command);
		}
	}
	return (command);
}
