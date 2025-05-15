/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:49:08 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/24 20:24:14 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;

	if ((!haystack[0] && !needle[0]) || !needle[0])
		return ((char *)haystack);
	i = 0;
	nlen = ft_strlen(needle);
	while (haystack[i] && i < len && len - i >= nlen)
	{
		if (ft_strncmp(haystack + i, needle, nlen) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
