#ifndef UTILS_H
#define UTILS_H

bool	char_in_set(char c, char *set);
int	ft_strcmp(const char *s1, const char *s2);
bool	is_quote(char character);
bool	is_space(char character);
bool	strnmatch(const char *s1, const char *s2, size_t n);
bool	strmatch(const char *s1, const char *s2);
char	peakch(char *str);
bool	str_blank(char *str);
void	print_strings(char **strings);

#endif
