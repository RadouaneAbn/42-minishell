#include <minishell.h>

void	token_printlst(t_token_lst *token_lst)
{
	while (token_lst)
	{
		print_token(token_lst->token);
		token_lst = token_lst->next;
	}
}
