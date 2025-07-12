#include <minishell.h>

void	put_unexpected_token_err(char *error)
{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd("'", 2);
}

t_tree *parser(t_token_lst *token_lst)
{
	t_tree *compound_command = tree_get_compound_command(&token_lst);
	if (token_lst)
	{
		if (!*syntax_err_value())
		{
			*syntax_err_value() = true;
			free_tree(compound_command);
			put_unexpected_token_err(token_lst->token.lexeme);
		}
		return (NULL);
	}
	return (compound_command);
}
