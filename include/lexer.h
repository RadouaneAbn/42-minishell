#ifndef LEXER_H
# define LEXER_H

# define END 1
# include <minishell.h>
typedef enum e_token_name
{
	AND,
	OR,
	HERE_DOC,
	APPEND_OUT,
	RED_IN,
	RED_OUT,
	PIPE,
	L_PAREN,
	R_PAREN,
	WORD
}	t_token_type;

typedef char*	t_token_value;

typedef struct s_token
{
	int		type;
	char				*lexeme;
}	t_token;

typedef struct s_token_lst
{
	t_token	*token;
	struct s_token_lst	*next;
}	t_token_lst;

void	lexer(char *line);
void	get_next_token(t_token **token, char *line);
void	print_token(t_token token);
bool	is_space(char c, char *spaces);

//lexer util functions
char *get_operator(int	index);
void	set_word_token(t_token **token, char *line, size_t *position);
void    set_operator_token(t_token **token, char *line, size_t *position);
int     get_operator_type(char *line, size_t *position);
bool    token_is_operator(char *line, size_t position);


/*======================== SOME USEFUL FUNCTIONS=====================*/
bool    strmatch(const char *s1,  const char *s2);
bool    strnmatch(const char *s1,  const char *s2, size_t n);
int     ft_strcmp(const char *s1, const char *s2);
bool    char_in_set(char c, char *set);
char	peakch(char *str);
bool	str_blank(char *str);


/*======================== token list manipulation functions=====================*/
t_token_lst	*token_lstnew(t_token *token);
t_token_lst	*token_lstlast(t_token_lst *lst);
void	token_lstadd_back(t_token_lst	**lst, t_token_lst *new);

#endif

