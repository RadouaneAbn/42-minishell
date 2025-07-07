/*#include <minishell.h>

create that function
void	consume()
{
}
//
//
t_tree	*tree_getsimple_command(t_token_lst **token_lst)
{
	t_tree;	
	//parse simple command to get=> argument_list[ls, -l] and redirect_list	
	if (issimple_command(token_lst))
		;
	else if (is_io_redirect(token_lst)
		;
}
//
t_tree	*tree_getsubshell(t_token_lst	**token_lst)
{
	t_tree	*command_list;
	t_tree	*redirect_list;
//
	command_list = tree_getcommand_list(token_lst);
	redirect_list = tree_getredirect_list(token_lst);
}
//
t_tree	tree_getcommand(t_token_lst **token_lst)
{
	t_tree	*command;
	bool	is_subshell;
	is_subshell = bool;
	// for subshell: consume '(' and call tree_getcommand_list
	if ((*token_lst)->token->type == L_PAREN)
	{
		var = true;
		*token_lst = (*token_lst)->next;
		command = tree_getcommand_list(token_lst);
	}
	//for simple command: 
	else
	{
		command = tree_getsimple_command(token_lst);	
	}
	return ();
}
//
t_tree *tree_getpipeline(t_token_lst **token_lst)
{
	t_tree	*command;
	t_tree	*pipeline;
//
	command = tree_getcommand(token_lst);
	pipeline = tree_getpipeline(token_lst);
//
	return ();
}
//
t_tree	*tree_getcompound_command(t_token_lst **token_lst)
{
	t_tree	*pipeline;
	t_tree	*logical_operator;
//
	pipeline = lstget_pipeline(token_lst);
//
	logical_operator = ;	
	compound_command = lstget_compound_command(token_lst);
//
	return ();
}
//
t_tree	*parser(t_token_lst *token_lst)
{
	return (lst_getcompound_command(token_lst));
}*/
