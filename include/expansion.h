#ifndef EXPANSION_H
#define EXPANSION_H
bool	valid_key_char(char c);
void	expand_word(char **str, size_t *index, char *complete_string);
void	expand_len(char *str);
char	*get_key(char **str);
bool	valid_key_char(char c);
size_t expand_word_len(char **str);
size_t expand_str_len(char *str);

void	tree_expand_simple_command(t_tree *simple_command);

void	expand(char *str, char *complete_string);
#endif
