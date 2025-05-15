#ifndef EXPANSION_H
#define EXPANSION_H
bool	valid_key_char(char c);
void	expand_word(char **str, size_t *index);
void	expand(char *str);
char	*get_key(char **str);
bool	valid_key_char(char c);
size_t expand_word_len(char **str);
size_t expand_str_len(char *str);
#endif
