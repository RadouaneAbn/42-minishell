/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:56:08 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 09:51:18 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void			set_operator_token(t_token *token,
					char *line, size_t *position);
void			set_word_token(t_token *token, char *line, size_t *position);
void			get_token(t_token *token, char *line, size_t *position);
void			get_next_token(t_token *token, char *line);
char			*get_operator(int index);
t_token_type	get_operator_type(char *line, size_t *position);
bool			token_is_operator(char *line, size_t position);
void			check_unclosed_quote(bool unclosed_quote);
void			syntax_err_signal_setup(int exit_status, bool *func(void));
bool			check_err_and_heredoc_signal(void);
void			lexer(char *line);
t_token_lst		*token_lstnew(t_token token);
t_token_lst		*token_lstlast(t_token_lst *lst);
void			token_lstadd_back(t_token_lst	**lst, t_token_lst *new);
void			sigint_handler(int sig);
#endif
