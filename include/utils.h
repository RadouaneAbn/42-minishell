/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:36:37 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 16:38:40 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <minishell.h>

int		ft_strcmp(const char *s1, const char *s2);
int		ft_index_of(char *str, char c);
t_info	*get_info(void);
void	load_env(char **env);
bool	is_dir(char *filename);

void	print_error(char *cmd, char *file, char *msg1, char *error_msg);

#endif