#include <minishell.h>

t_tree	*tree_get_argument(t_token_lst	**token_lst)
{
	t_tree	*new_arg;
	int	data_type;
	char	*parameter;

	data_type = T_CMD_ARG;
	parameter = strdup((*token_lst)->token.lexeme);
	new_arg = tree_create_new(data_type, parameter);
	(*token_lst) = (*token_lst)->next;
	return (new_arg);
}

t_tree	*tree_get_io_redirect(t_token_lst	**token_lst)
{
	t_tree	*new_io_redirect;
	int	data_type;
	char	*parameter;

	data_type = (*token_lst)->token.type;
	*token_lst = (*token_lst)->next;
	new_io_redirect = NULL;
	if (*token_lst)
	{
		if ((*token_lst)->token.type == WORD)
		{
			if (data_type == HERE_DOC)
				parameter = here_doc((*token_lst)->token.lexeme);
			else
				parameter = strdup((*token_lst)->token.lexeme);
			new_io_redirect = tree_create_new(data_type, parameter);
		}
		else
			printf ("syntax error near unexpected token '%s'\n", (*token_lst)->token.lexeme);
		*token_lst = (*token_lst)->next;
	}
	else
		printf ("syntax error near unexpected token '\\n''");

	return (new_io_redirect);
}

t_tree	*parse_simple_command(t_token_lst	**token_lst)
{
	t_tree	*args = NULL;
	t_tree	*io_files = NULL;
	t_tree	*simple_command;
	while (*token_lst)
	{
		if (is_redirect_operator((*token_lst)->token.type))
			tree_add_back(&io_files, tree_get_io_redirect(token_lst));
		else if (is_token_word((*token_lst)->token.type))
			tree_add_back(&args, tree_get_argument(token_lst));
		else
			break ;
	}

	if (!args && !io_files)
		return (NULL);

	tree_add_sibling_back(&args, io_files);
	simple_command = args;
	return (simple_command);
}
