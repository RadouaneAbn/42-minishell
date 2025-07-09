#include <minishell.h>

void	lexer(char *line)
{
	t_token		token;
	t_token_lst	*new_node;
	t_token_lst	*token_lst;
	t_tree	*tree;

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
	tree = parser(token_lst);
	print_tree(tree, 0);
	tree_expand_simple_command(tree->next->next->next);
	token_free_list(token_lst);
}
