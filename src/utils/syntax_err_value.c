#include <minishell.h>

bool	*syntax_err_value(void)
{
	static bool	syntax_err;

	return (&syntax_err);
}
