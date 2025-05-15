/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:09:25 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/25 19:55:23 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_final_len(char const *s1, char const *set, size_t *s)
{
	size_t	end;

	if (!s1[0])
		return (0);
	*s = 0;
	end = ft_strlen(s1) - 1;
	while (s1[*s] && ft_strchr(set, s1[*s]))
		(*s)++;
	if (*s >= end)
		return (end);
	while (s1[end] && ft_strchr(set, s1[end]))
		end--;
	return (end - (*s) + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	new_size;
	size_t	start;

	if (s1 == NULL)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	new_size = get_final_len(s1, set, &start);
	new_str = ft_substr(s1, start, new_size);
	return (new_str);
}
