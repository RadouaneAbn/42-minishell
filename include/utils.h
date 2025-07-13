#ifndef UTILS_H
#define UTILS_H

#define REINITIALIZE true
#define RESUME false

bool	char_in_set(char c, char *set);
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

//temprory
// int	get_exit_code(void);

void	gc_global_free(void *ptr);

void	free_strings(char **strings);
void	free_list(t_list **list);
void	free_token_list(t_token_lst **list);

bool *syntax_err_value(void);

char	**lst_to_strings(t_list *list);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_index_of(char *str, char c);
t_info	*get_info(void);
void	load_env(char **env);
bool	is_dir(char *filename);
char *copy_string(char *src);
bool *ps_status(void);
void	print_error(char *cmd, char *file, char *msg1, char *error_msg);

#endif
