#include <parser.h>

bool	is_operator(int	type)
{
	return (type == RED_IN || type == RED_OUT
		|| type == APPEND_OUT || type == HERE_DOC);
}

//function idea: report
//function idea: throw
//function tree_append
void	parse_simple_command(t_token_lst	*token_lst)
{
	//t_list	*outfiles;
	//t_list	*infiles;
	//t_list	*cmd;

	int	redirect_operator;

	redirect_operator = -1;
	while (token_lst)
	{
		if (is_operator(token_lst->token->type) && redirect_operator == -1)
			redirect_operator = token_lst->token->type;
		else if (token_lst->token->type == WORD && redirect_operator != -1)
		{
			if (redirect_operator == HERE_DOC)
				printf("delimeter: "BLUE"%s"RESET" %s\n", token_lst->token->lexeme, get_operator(redirect_operator));
			else
				printf("file: "BLUE"%s"RESET" %s\n", token_lst->token->lexeme, get_operator(redirect_operator));
			redirect_operator = -1;
		}
		else if (token_lst->token->type == WORD && redirect_operator == -1)
			printf("arg: %s arg_list\n", token_lst->token->lexeme);
		else if (token_lst->token->type != WORD && redirect_operator != -1)
		{
			printf ("syntax error near unexpected token '%s'\n", token_lst->token->lexeme);
			break ;
		}
		else
			break;
		token_lst = token_lst->next;
	}
	if (redirect_operator != -1)
			printf ("syntax error near unexpected token 'end of line'\n");
}

t_tree	*parse_simple_command(t_token_lst	**token_lst)
{
	t_tree	*simple_command;
	t_tree	*io_redirect;
	t_tree	argument_list;

	while ((*token_lst))
	{
		if ((is_operator((*token_lst)->token->type))
			io_redirect->next = tree_get_io_redirect(token_lst);
		else if ((*token_lst)->token == WORD)
			argument_list->next = tree_get_argument(token_lst);
		else
			break ;
	}
}

t_tree *tree_create_new(int data_type, char *parameter)
{
	t_tree	*new;

	new = malloc(sizeof(t_tree));
	if (new == NULL)
		return (NULL);
	new->data_type = data_type;		
	new->data = parameter;
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
	else if ((*token_lst)->token->type == WORD && redirect_operator == HERE_DOC)
	{
		//run_heredoc();
		//new->data_type = redirect_operator;
		//new->data = file_name;
	}
	else
		printf ("syntax error near unexpected token '%s'\n", token_lst->token->lexeme);
	return (new_io_redirect);
}
