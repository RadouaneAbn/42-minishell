#ifndef LEXER_H
# define LEXER_H
# define END 1

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
}						t_token_type;

typedef char			*t_token_value;

typedef struct s_token
{
	int					type;
	char				*lexeme;
}						t_token;

typedef struct s_token_lst
{
	t_token				token;
	struct s_token_lst	*next;
}						t_token_lst;

void	lexer(char *line);
void	get_next_token(t_token *token, char *line);
void	print_token(t_token token);
bool	is_space(char character);

//lexer util functions
char *get_operator(int	index);
void	set_word_token(t_token *token, char *line, size_t *position);
void    set_operator_token(t_token *token, char *line, size_t *position);
t_token_type     get_operator_type(char *line, size_t *position);
void	get_token(t_token *token, char *line, size_t *position);
bool    token_is_operator(char *line, size_t position);
void	token_printlst(t_token_lst *token_lst);
void	check_unclosed_quote(bool unclosed_quote);

/*======================== token list manipulation functions=====================*/
t_token_lst				*token_lstnew(t_token token);
t_token_lst				*token_lstlast(t_token_lst *lst);
void					token_lstadd_back(t_token_lst **lst, t_token_lst *new);

#endif
