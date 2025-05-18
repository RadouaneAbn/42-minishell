#include <lexer.h>

void	parser(t_token_lst *token_lst)
{
	while (token_lst)
	{
		token_lst = token_lst->next;
	}
}
