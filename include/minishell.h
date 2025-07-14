#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <garbage_collector.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <colors.h>
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <lexer.h>
# include <parser.h>
# include <expansion.h>
# include <pathname_expansion.h>
# include <unistd.h>
# include <hashmap.h>
# include <execution.h>
# include <built_in.h>
# include <utils.h>
# include <garbage_collector.h>
# include <signal.h>

# define MALLOC_FAILURE 42

void sigint_handler(int sig);

#endif
