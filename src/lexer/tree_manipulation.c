#include <parser.h>

t_tree	tree_getsimple_command(t_token_lst **token_lst)
{
	// we have two methods
	// 1: create a new function for io|redirection
	// use a function to parse command and return command
}

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

t_tree tree_getpipeline(t_token_lst **token_lst)
{
	t_tree	*command;
	t_tree	*pipeline;

	command = tree_getcommand(token_lst);
	pipeline = tree_getpipeline(token_lst);

	return ();
}

t_tree	tree_getcompound_command(t_token_lst **token_lst)
{
	t_tree	*pipeline;
	t_tree	*logical_operator;

	pipeline = lstget_pipeline(token_lst);

	logical_operator = ;	
	compound_command = lstget_compound_command(token_lst);

	return ();
}

t_tree	*parser(t_token_lst *token_lst)
{
	return (lst_getcompound_command(token_lst));
}
