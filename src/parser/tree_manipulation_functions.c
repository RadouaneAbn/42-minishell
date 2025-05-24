#include <minishell.h>

t_tree	*tree_get_argument(t_token_lst	**token_lst)
{
	t_tree	*new_arg;
	int	data_type;
	char	*parameter;

	data_type = 3;
	parameter = strdup((*token_lst)->token->lexeme);
	new_arg = tree_create_new(data_type, parameter);
	(*token_lst) = (*token_lst)->next;
	return (new_arg);
}

t_tree	*tree_get_io_redirect(t_token_lst	**token_lst)
{
	t_tree	*new_io_redirect;
	int	data_type;
	char	*parameter;

	data_type = is_output_redirection_operator((*token_lst)->token->type) == true;
	*token_lst = (*token_lst)->next;
	new_io_redirect = NULL;
	if (*token_lst)
	{
		if ((*token_lst)->token->type == WORD)
		{
			parameter = strdup((*token_lst)->token->lexeme);
			new_io_redirect = tree_create_new(data_type, parameter);
		}
		else
			printf ("syntax error near unexpected token '%s'\n", (*token_lst)->token->lexeme);
		*token_lst = (*token_lst)->next;
	}
	else
		printf ("syntax error near unexpected token '\n''");

	return (new_io_redirect);
}

bool	is_output_redirection_operator(int	operator)
{
	return (operator == APPEND_OUT || operator == RED_OUT);
}

bool	is_input_redirection_operator(int	operator)
{
	return (operator == RED_IN || operator == HERE_DOC);
}

bool	is_token_word(int	operator)
{
	return (operator == WORD);
}

t_tree	*parse_simple_command(t_token_lst	**token_lst)
{
	t_tree	*argument_list = NULL;
	t_tree	*io_redirect_list = NULL;
	t_tree	*simple_command = NULL;
	t_tree	*args = NULL;
	t_tree	*infiles = NULL;
	t_tree	*outfiles = NULL;

	//create argument list tree T_ARG_LIST T_SIMPLE_CMD
	argument_list = tree_create_new(4, NULL);

	io_redirect_list = tree_create_new(6, NULL);;
	// create simple command tree simple_command N=> argument_list S=> io_redirect_list
	simple_command = tree_create_new(5, NULL);	

	while (*token_lst)
	{
		if (is_output_redirection_operator((*token_lst)->token->type))
			tree_add_back(&outfiles, tree_get_io_redirect(token_lst));
		else if (is_input_redirection_operator((*token_lst)->token->type))
			tree_add_back(&infiles, tree_get_io_redirect(token_lst));
		else if (is_token_word((*token_lst)->token->type))
			tree_add_back(&args, tree_get_argument(token_lst));
		else
			break ;
		//(*token_lst) = (*token_lst)->next;
	}
	// add args to argument_list
	tree_add_back(&argument_list, args);

	// add infiles and outfiles to input/output redirect list
	if (outfiles)
		tree_add_back(&io_redirect_list, outfiles);
	else if (infiles)
		tree_add_back(&io_redirect_list, infiles);
	tree_add_sibling_back(&outfiles, infiles);

	// and finally add both of them to simple command
	tree_add_back(&simple_command, argument_list);
	tree_add_sibling_back(&argument_list, io_redirect_list);

	return (simple_command);
}
