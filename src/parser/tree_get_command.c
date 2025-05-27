#include <minishell.h>

void	consume(t_token_lst **token_lst)
{
	(*token_lst) = (*token_lst)->next;
}

t_tree	*tree_get_io_redirect_list(t_token_lst	**token_lst)
{
	t_tree	*io_redirect_list;
	t_tree	*infiles;
	t_tree	*outfiles;

		printf("%s\n", (char *)(*token_lst)->token->lexeme);
	io_redirect_list = tree_create_new(6, NULL);
	infiles = NULL;
	outfiles = NULL;
	while ((*token_lst))
	{
		if (is_output_redirection_operator((*token_lst)->token->type))
		{	
			printf("hey");
			tree_add_back(&outfiles, tree_get_io_redirect(token_lst));
		}
		else if (is_input_redirection_operator((*token_lst)->token->type))
			tree_add_back(&infiles, tree_get_io_redirect(token_lst));
		else
			break ;
	}
	if (outfiles)
	{
		tree_add_back(&io_redirect_list, outfiles);
	}
	else if (infiles)
		tree_add_back(&io_redirect_list, infiles);
	tree_add_sibling_back(&outfiles, infiles);
	return (io_redirect_list);
}

t_tree	*parse_subshell(t_token_lst	**token_lst)
{
	t_tree	*simple_command;
	t_tree	*io_redirect_list;
	t_tree	*subshell;

	consume(token_lst);
	simple_command = tree_get_command(token_lst);
	//if (!(*token_lst) || (!simple_command->next->next && !simple_command->next->sibling->next))
	//{
	//printf("error\n");
	//exit (2);
	//}
	if ((*token_lst)->token->type == R_PAREN)
		consume(token_lst);
	subshell = tree_create_new(7, NULL);
	if ((*token_lst))
	{
		io_redirect_list = tree_get_io_redirect_list(token_lst);
		tree_add_sibling_back(&subshell, io_redirect_list);
	}
	tree_add_back(&subshell, simple_command);
	return (subshell);
}

t_tree	*tree_get_command(t_token_lst **token_lst)
{
	t_tree	*command;
	t_tree	*subshell;
	t_tree	*simple_command;

	command = tree_create_new(8, NULL);
	simple_command = NULL;
	//for subshell: consume '(' and call tree_getcommand_list and then consume ')'
	if ((*token_lst)->token->type == L_PAREN)
	{
		subshell = parse_subshell(token_lst);
		tree_add_back(&command, subshell);
	}
	//for simple command: 
	else
	{
		simple_command = parse_simple_command(token_lst);
		tree_add_back(&command, simple_command);
	}
	return (command);
}
