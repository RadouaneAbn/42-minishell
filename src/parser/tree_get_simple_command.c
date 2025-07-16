/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:35:38 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 20:12:02 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tree	*tree_get_argument(t_token_lst	**token_lst)
{
	t_tree	*new_arg;
	int		data_type;
	char	*parameter;

	data_type = T_CMD_ARG;
	parameter = ft_strdup((*token_lst)->token.lexeme);
	new_arg = tree_create_new(data_type, parameter);
	(*token_lst) = (*token_lst)->next;
	return (new_arg);
}

bool	tree_set_io_redirect(t_token_lst	**token_lst,
		t_tree **new_io_redirect, int data_type, char *parameter)
{
	if ((*token_lst)->token.type == WORD)
	{
		if (data_type == HERE_DOC)
		{
			parameter = heredoc((*token_lst)->token.lexeme);
			if (parameter == NULL)
			{
				*heredoc_signaled() = true;
				return (true);
			}
		}
		else
			parameter = ft_strdup((*token_lst)->token.lexeme);
		*new_io_redirect = tree_create_new(data_type, parameter);
	}
	else
		return (true);
	consume(token_lst);
	return (false);
}

t_tree	*tree_get_io_redirect(t_token_lst	**token_lst)
{
	t_tree	*new_io_redirect;
	int		data_type;
	char	*parameter;
	int		syntax_err;

	data_type = (*token_lst)->token.type;
	*token_lst = (*token_lst)->next;
	new_io_redirect = NULL;
	parameter = NULL;
	syntax_err = false;
	if (*token_lst)
	{
		syntax_err = tree_set_io_redirect(token_lst,
				&new_io_redirect, data_type, parameter);
		if (syntax_err)
			return (NULL);
	}
	else
	{
		*(syntax_err_value()) = true;
		ft_putendl_fd ("syntax error near unexpected token '\\n''", 2);
	}
	return (new_io_redirect);
}

bool	tree_set_simple_command(t_token_lst **token_lst,
		t_tree **tree_ptr, t_tree *(tree_func)(t_token_lst **))
{
	t_tree	*new_tree;

	new_tree = tree_func(token_lst);
	if (!new_tree)
		return (true);
	tree_add_back(tree_ptr, new_tree);
	return (false);
}

t_tree	*tree_get_simple_command(t_token_lst	**token_lst)
{
	t_tree	*args;
	t_tree	*io_files;
	t_tree	*simple_command;
	bool	syntax_err;

	syntax_err = false;
	args = NULL;
	io_files = NULL;
	while (*token_lst)
	{
		if (is_redirect_operator((*token_lst)->token.type))
			syntax_err = tree_set_simple_command(token_lst,
					&io_files, tree_get_io_redirect);
		else if (is_token_word((*token_lst)->token.type))
			syntax_err = tree_set_simple_command(token_lst,
					&args, tree_get_argument);
		else
			break ;
		if (syntax_err)
			return (free_tree(&args), free_tree(&io_files), NULL);
	}
	tree_add_sibling_back(&args, io_files);
	simple_command = args;
	return (simple_command);
}
