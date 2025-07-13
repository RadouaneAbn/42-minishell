#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
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
