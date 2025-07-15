/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:40:02 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/15 23:41:14 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define REINITIALIZE true
# define RESUME false
# define UID_SIZE 28
# define ID_UNIQ_CHARS_SIZE 12
# define READ_SIZE 24

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
char	*utoa(size_t num);
void	token_free_list(t_token_lst *token_lst);

// temprory
// int	get_exit_code(void);

void	free_strings(char **strings);
void	free_list(t_list **list);
void	free_token_list(t_token_lst **list);

bool	*syntax_err_value(void);

char	**lst_to_strings(t_list *list);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_index_of(char *str, char c);
t_info	*get_info(void);
void	load_env(char **env);
bool	is_dir(char *filename);
char	*copy_string(char *src);
bool	*ps_status(void);
void	print_error(char *cmd, char *file, char *msg1, char *error_msg);
void	set_exit_status(int exit_status);
void	clean_exit(int exit_code);
char	*id(void);

#endif
