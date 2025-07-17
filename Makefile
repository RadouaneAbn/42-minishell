SOURCE_FILES = src/built_in/buildin_exit.c src/built_in/buildin_utils_2.c src/built_in/buildin_utils.c \
							 src/built_in/cd.c src/built_in/echo.c src/built_in/expand.c \
							 src/built_in/export.c src/built_in/print_env.c src/built_in/run_built_in_2.c \
							 src/built_in/run_built_in.c src/built_in/unset.c src/execution/execute_command.c \
							 src/execution/execute_tree.c src/execution/execute_tree_helper.c src/execution/execution_utils_2.c \
							 src/execution/execution_utils.c src/execution/exit_status.c src/execution/file_redirection.c \
							 src/execution/print_error.c src/execution/redirections.c src/execution/run_pipe.c \
							 src/execution/subshell.c src/expansion/bitwise_utils.c src/expansion/expand_command.c \
							 src/expansion/expand_strlen.c src/expansion/expansion.c src/expansion/field_splitting.c \
							 src/expansion/field_splitting_utils.c src/expansion/parameter_expansion_utils.c src/gc/garbage_collector.c \
							 src/gc/gc_alloc.c src/gc/gc_free.c src/gc/gc_tools.c \
							 src/heredoc/heredoc.c src/heredoc/heredoc_expansion.c src/heredoc/heredoc_utils.c \
							 src/lexer/get_next_token.c src/lexer/get_next_token_utils.c src/lexer/lexer.c \
							 src/lexer/list_manipulate_functions.c src/lexer/main.c src/parser/parser.c \
							 src/parser/token_lst_utils.c src/parser/tree_get_command.c src/parser/tree_get_compound_command.c \
							 src/parser/tree_get_pipeline.c src/parser/tree_get_simple_command.c src/parser/tree_get_subshell.c \
							 src/pathname_expansion/pathname_expansion.c src/pathname_expansion/pathname_expansion_utils.c src/tree_utils/free_tree.c \
							 src/tree_utils/tree_add_back.c src/tree_utils/tree_add_sibling_back.c src/tree_utils/tree_create_new.c \
							 src/tree_utils/tree_get_last.c src/tree_utils/tree_get_last_sibling.c src/tree_utils/tree_get_size.c \
							 src/utils/char_in_set.c src/utils/clean_exit.c src/utils/copy_string.c \
							 src/utils/free_lst.c src/utils/free_strings.c src/utils/free_token_list.c \
							 src/utils/ft_index_of.c src/utils/ft_strcmp.c src/utils/get_strings_len.c \
							 src/utils/hash.c src/utils/hashmap.c src/utils/hashmap_utils.c \
							 src/utils/heredoc_signaled.c src/utils/here_doc_uid.c src/utils/is_dir.c \
							 src/utils/is_quote.c src/utils/is_removable_quote.c src/utils/is_space.c \
							 src/utils/load_env.c src/utils/lst_to_strings.c src/utils/peakch.c \
							 src/utils/shell_info.c src/utils/str_blank.c src/utils/strmatch.c \
							 src/utils/strnmatch.c src/utils/syntax_err_value.c 

OBJECT_FILES = $(SOURCE_FILES:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra

INCLUDE = include
TARGET = minishell

all: $(TARGET)

bonus: $(TARGET)

$(TARGET): $(OBJECT_FILES) libft/libft.a
	$(CC) $^ -o $@  -lreadline
	
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
	$(RM) $(RM_OPTIONS) $(OBJECT_FILES) 
	make clean -C libft

libft/libft.a:
	make -C libft bonus

fclean: clean
	$(RM) $(RM_OPTIONS) $(TARGET)
	make fclean -C libft

re: fclean $(TARGET)

fvalgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes -s ./$(TARGET)
