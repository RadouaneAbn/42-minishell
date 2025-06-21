#include <minishell.h>

void	token_free_list(t_token_lst *token_lst);
void	lexer(char *line)
{
	t_token	token;
	t_token_lst	*new_node;
	t_token_lst	*token_lst;

	token_lst = NULL;
	while (true)
	{
		token.lexeme = NULL;
		get_next_token(&token, line);
		if (token.lexeme == NULL)
			break ;
		new_node = token_lstnew(token);
		token_lstadd_back(&token_lst, new_node);
	}
	//token_printlst(token_lst);
	t_tree *tree = parser(token_lst);
	print_tree(tree, 0);
	tree_expand_simple_command(tree->next->next->next);
	token_free_list(token_lst);
}

void	token_printlst(t_token_lst *token_lst)
{
	while (token_lst)
	{
		print_token(token_lst->token);
		token_lst = token_lst->next;
	}
}

void	token_free_list(t_token_lst *token_lst)
{
	t_token_lst	*tmp;

	while (token_lst)
	{
		tmp = token_lst->next;
		free(token_lst->token.lexeme);
		free(token_lst);
		token_lst = tmp;
	}
}
