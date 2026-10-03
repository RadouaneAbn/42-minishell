/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:48:38 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:48:39 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	first_key_ch(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

bool	key_ch(char c)
{
	return (ft_isalpha(c) || c == '_' || ft_isdigit(c));
}

char	*get_key(char **str)
{
	char	*key;
	size_t	len;

	len = 0;
	while (key_ch((*str)[len]))
		len++;
	key = ft_substr(*str, 0, len);
	if (key == NULL)
		return (NULL);
	*str += len;
	return (key);
}
