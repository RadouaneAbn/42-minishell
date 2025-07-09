#include <minishell.h>

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
