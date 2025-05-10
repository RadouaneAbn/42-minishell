/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:18:35 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/07 11:07:21 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	character;

	if (s == 0)
		return (0);
	character = (char)c;
	while (*s != '\0')
	{
		if (*s == character)
			return ((char *)s);
		s++;
	}
	if (character == '\0')
		return ((char *)s);
	return (0);
}
