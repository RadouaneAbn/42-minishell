#ifndef UTILS_H
#define UTILS_H
bool	char_in_set(char c, char *set);
int	ft_strcmp(const char *s1, const char *s2);
bool	is_quote(char character);
bool	is_space(char character);
bool	is_removable_quote(char character, bool reset);
bool	strnmatch(const char *s1, const char *s2, size_t n);
bool	strmatch(const char *s1, const char *s2);
char	peakch(char *str);
bool	str_blank(char *str);
void	print_strings(char **strings);
size_t	get_strings_len(char **strings);
char    *utoa(size_t num);
void	token_free_list(t_token_lst *token_lst);
#endif
