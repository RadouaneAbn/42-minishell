#include <parser.h>

bool	syntax_error(bool error)
{
	static bool	err;

	if (error)
		err = error;
	return (err);
}

void	get_subshell(t_token_lst	**token_lst)
{
		printf("[");
		while (*token_lst)
		{
			if ((*token_lst)->token->type == L_PAREN)
				get_subshell(&(*token_lst)->next);
			else if ((*token_lst)->token->type == R_PAREN)
			{
				*token_lst = (*token_lst)->next;
				printf("]\n");
				return ;
			}
			else
				printf("%s", (*token_lst)->token->lexeme);
			if (syntax_error(false))
				return ;
			*token_lst = (*token_lst)->next;

		}
		syntax_error(true);
		if (syntax_error(false))
			printf("error");
}


