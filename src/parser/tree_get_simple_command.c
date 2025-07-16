/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:35:38 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 19:24:19 by hsacr            ###   ########.fr       */
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

t_tree	*tree_get_io_redirect(t_token_lst	**token_lst)
{
	t_tree	*new_io_redirect;
	int		data_type;
	char	*parameter;

	data_type = (*token_lst)->token.type;
	*token_lst = (*token_lst)->next;
	new_io_redirect = NULL;
	if (*token_lst)
	{
		if ((*token_lst)->token.type == WORD)
		{
			if (data_type == HERE_DOC)
			{
				parameter = heredoc((*token_lst)->token.lexeme);
				if (parameter == NULL)
				{
					*heredoc_signaled() = true;
					return (NULL);
				}
			}
			else
				parameter = ft_strdup((*token_lst)->token.lexeme);
			new_io_redirect = tree_create_new(data_type, parameter);
		}
		else
			return (NULL);
		*token_lst = (*token_lst)->next;
	}
	else
	{
		*(syntax_err_value()) = true;
		ft_putendl_fd ("syntax error near unexpected token '\\n''", 2);
	}
	return (new_io_redirect);
}

bool	tree_set_simple_command(t_token_lst **token_lst, t_tree **tree_ptr, t_tree *(tree_func)(t_token_lst **))
{
	t_tree	*new_tree;

	new_tree = tree_func(token_lst);
	if (!new_tree)
		return (true);	
	tree_add_back(tree_ptr, new_tree);
	return (false);
}

t_tree	*parse_simple_command(t_token_lst	**token_lst)
{
	t_tree	*args;
	t_tree	*io_files;
	t_tree	*simple_command;
	//t_tree	*io_redirect;
	//t_tree	*argument;
	bool		syntax_err;

	syntax_err = false;
	args = NULL;
	io_files = NULL;
	while (*token_lst)
	{
		if (is_redirect_operator((*token_lst)->token.type))
		{
			syntax_err = tree_set_simple_command(token_lst, &io_files, tree_get_io_redirect);
			//io_redirect = tree_get_io_redirect(token_lst);
			//if (!io_redirect)
				//syntax_err = true;
			//tree_add_back(&io_files, io_redirect);
		}
		else if (is_token_word((*token_lst)->token.type))
		{
			syntax_err = tree_set_simple_command(token_lst, &args, tree_get_argument);
			//argument = tree_get_argument(token_lst);
			//if (!argument)
				//syntax_err = true;
			//tree_add_back(&args, argument);
		}
		else
			break ;
		if (syntax_err)
		{
			free_tree(&args);
			free_tree(&io_files);
			return (NULL);
		}
	}
	tree_add_sibling_back(&args, io_files);
	simple_command = args;
	return (simple_command);
}
