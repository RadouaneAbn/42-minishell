#include <parser.h>

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

void	tree_add_sibling_back(t_tree **head, t_tree *new)
{
	t_tree	*last_sibling;

	if (*head == NULL)
		(*head) = new;
	else
	{
		last_sibling = tree_get_last_sibling(*head);
		last_sibling->sibling = new;
	}
}

void	tree_add_back(t_tree **head, t_tree *new)
{
	t_tree	*last_node;

	if (*head == NULL)
		(*head) = new;
	else
	{
		last_node = tree_get_last(*head);
		last_node->next = new;
	}
}

t_tree	*parse_simple_command(t_token_lst	**token_lst)
{
	t_tree	*argument_list;
	t_tree	*io_redirect_list;
	t_tree	*simple_command;
	t_tree	*args;
	t_tree	*infiles;
	t_tree	*outfiles;

	//create argument list tree
	argument_list = tree_create_new(T_ARG_LIST, NULL);

	// create simple command tree simple_command N=> argument_list S=> io_redirect_list
	simple_command = tree_create_new(T_SIMPLE_CMD, NULL);	

	while (*token_lst)
	{
		if (is_output_redirection_operator((*token_lst)->token->type)
			tree_add_sibling_back(&infiles, tree_get_io_redirect(token_lst));
		else if (is_input_redirection_operator((*token_lst)->token->type)
			tree_add_sibling_back(&outfiles, tree_get_io_redirect(token_lst));
		else if (is_token_word((*token_lst)->token->type)
			tree_add_sibling_back(&args, tree_get_argument(token_lst));
		else
			break ;
		(*token_lst) = (*token_lst)->next;
	}
	// add args to argument_list
	tree_add_back(&argument_list, args);

	// add infiles and outfiles to input/output redirect list
	tree_add_back(&io_redirect_list, outfiles);
	tree_add_back(&io_redirect_list, infiles);

	// and finally add both of them to simple command
	tree_add_back(&simple_command, argumen_list);
	tree_add_sibling(
	simple_command->next = argument_list;
	argument_list->next = io_redirect_list->next;
	return (simple_command);
}

t_tree *tree_create_new(int data_type, void *parameter)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->data_type = data_type;
	new->data = parameter;
	new->next = NULL;
	new->sibling = NULL;
	return (new);
}

t_tree	*tree_get_argument(t_token_lst	**token_lst)
{
	t_tree	*new_arg;
	int	data_type;
	char	*parameter;

	data_type = 2;
	parameter = strdup((*token)->token->lexeme);
	new_arg = tree_create_new(data_type, parameter);
	(*token_lst) = (*token_lst)->next;
	return (new_arg);
}

t_tree	*tree_get_io_redirect(t_token_lst	**token_lst)
{
	t_tree	*new_io_redirect;

	int	data_type;
	char	*parameter;
	redirect_operator = (*token_lst)->token->type;
	*token_lst = (*token_lst)->next;

	if ((*token_lst)->token->type == WORD && redirect_operator != HERE_DOC)
	{
		data_type = redirect_operator; 
		parameter = strdup((*token_lst)->token->lexeme);
		new_io_redirect = tree_create_new(data_type, parameter);
	}
	//else if ((*token_lst)->token->type == WORD && redirect_operator == HERE_DOC)
	//{
		////run_heredoc();
		////new->data_type = redirect_operator;
		////new->data = file_name;
	//}
	else
		printf ("syntax error near unexpected token '%s'\n", token_lst->token->lexeme);
	*token_lst = (*token_lst)->next;

	return (new_io_redirect);
}
