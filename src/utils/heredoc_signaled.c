#include <minishell.h>

bool	*heredoc_signaled(void)
{
	static bool	is_signaled;

	return (&is_signaled);
}
