#include <minishell.h>

void	token_printlst(t_token_lst *token_lst);
void	lexer(char *line)
{
	t_token	*token;
	t_token_lst	*new_node;
	t_token_lst	*token_lst;

	token_lst = NULL;
	while (true)
	{
		token = NULL;
		get_next_token(&token, line);
		if (token == NULL)
			break ;
		new_node = token_lstnew(token);
		token_lstadd_back(&token_lst, new_node);
	}
	//token_printlst(token_lst);
	t_tree *tree = parser(&token_lst);
	print_tree(tree, 0);
	//parser(token_lst);
}

void	token_printlst(t_token_lst *token_lst)
{
	while (token_lst)
	{
		print_token(*(token_lst->token));
		token_lst = token_lst->next;
	}
}
