#ifndef EXPANSION_H
#define EXPANSION_H
bool	valid_key_char(char c);
void	expand_word(char **str, size_t *index);
void	expand(char *str);
#endif
