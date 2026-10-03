/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:39 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/16 12:24:08 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	expand_word_len(char **str)
{
	size_t	len;
	char	*key;
	int		exit_code_len;
	char	*exit_code;
	char	*value;

	len = 0;
	if (peakch(*str) == '?')
	{
		exit_code = ft_itoa(get_exit_status());
		exit_code_len = ft_strlen(exit_code);
		len += exit_code_len;
		*str += 2;
		gc_local_free(exit_code);
		return (len);
	}
	(*str)++;
	key = get_key(str);
	value = expand_env(key);
	if (key == NULL)
		return (0);
	gc_local_free(key);
	return (ft_strlen(value));
}

size_t	expand_str_len(char *str)
{
	bool	quoted;
	char	quote;
	size_t	len;

	quoted = false;
	len = 0;
	while (*str)
	{
		if (is_removable_quote(*str, RESUME))
		{
			quoted = !quoted;
			if (quoted)
				quote = *str;
		}
		if (((quoted && (quote == '"')) || !quoted) && *str == '$'
			&& first_key_ch(peakch(str)))
			len += expand_word_len(&str);
		else
		{
			len++;
			str++;
		}
	}
	is_removable_quote(*str, REINITIALIZE);
	return (len);
}
