#include <minishell.h>

t_tree *parser(t_token_lst *token_lst)
{
	t_tree *compound_command = tree_get_compound_command(&token_lst);
	if (token_lst)
	{
		printf("error [%s]\n", token_lst->token.lexeme);
		return (NULL);
	}
	return (compound_command);
}
