/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:19:56 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/07 11:24:36 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_strtrim_valid(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (*(set + i) != '\0')
	{
		if (c == *(set + i))
			return (0);
		i++;
	}
	return (1);
}

static size_t	ft_strtrim_length(char const *s1, char const *set)
{
	long	start;
	long	end;
	int		found;
	size_t	length;

	found = 0;
	start = 0;
	length = 0;
	while (*(s1 + start) != '\0' && !ft_strtrim_valid(*(s1 + start), set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= 0 && !found)
	{
		if (!ft_strtrim_valid(*(s1 + end), set))
			end--;
		else
			found = 1;
	}
	if (end >= start)
		length = end - start + 1;
	return (length);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;

	if (s1 == 0)
		return (0);
	if (set == 0)
		return (ft_strdup(s1));
	i = 0;
	ptr = (char *)malloc((ft_strtrim_length(s1, set) + 1) * sizeof(char));
	if (ptr == 0)
		return (ft_strdup(""));
	while (!ft_strtrim_valid(*s1, set))
		s1++;
	while (i < ft_strtrim_length(s1, set))
	{
		*(ptr + i) = *(s1 + i);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
