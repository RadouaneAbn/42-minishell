/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:14:40 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/17 09:40:50 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATHNAME_EXPANSION_H
# define PATHNAME_EXPANSION_H

char	get_last_char(char *str);
bool	check_pattern(char *filename, char *pattern, char *star_mask);
void	get_child_files(t_tree **tree, char *pattern, char *star_mask);
t_list	*pathname_expansion(char **fields, t_list *star_mask);
size_t	get_star_fields_len(char *str, char *star_mask);
void	define_star_field(char **parts, char *str,
			size_t *index, char *star_mask);
void	set_star_fields(char **parts, char *str, char *star_mask);
char	**get_star_fields(char *str, char *star_mask);

#endif
