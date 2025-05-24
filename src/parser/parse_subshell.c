#include <minishell.h>

//t_tree	*parse_subshell(t_token_lst	**token_lst)
//{
//while ((*token))
//{
//(*token) = (*token)->
//
//}

void	consume(t_token_lst **token_lst)
{
	(*token_lst) = (*token_lst)->next;
}

t_tree	*tree_get_command(t_token_lst **token_lst)
{
	t_tree	*command;
	t_tree	*subshell;

	command = NULL;
	subshell = tree_create_new(2, NULL);
	//for subshell: consume '(' and call tree_getcommand_list and then consume ')'
	if ((*token_lst)->token->type == L_PAREN)
	{
		consume(token_lst);
		command = parse_simple_command(token_lst);
		if (!(*token_lst))
		{
			printf("error\n");
		exit (2);
		}
	}
	//for simple command: 
	//else
	//command = tree_get_simple_command(token_lst);	
	tree_add_back(&subshell, command);
	return (subshell);
}
