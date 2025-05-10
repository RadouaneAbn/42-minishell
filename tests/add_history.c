#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	add_history("Hello World!");

	printf("number of history entries: %d\n", history_length);

	add_history("Hello World! again!!");

	printf("number of history entries: %d\n", history_length);

	rl_clear_history();

	return (0);
}
