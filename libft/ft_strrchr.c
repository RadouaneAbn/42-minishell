/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:09:24 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/12 11:05:37 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	character;

	i = 0;
	character = (char)c;
	while (*(s + i) != '\0')
		i++;
	if (character == '\0')
		return ((char *)(s + i));
	while (i--)
		if (*(s + i) == character)
			return ((char *)(s + i));
	return (0);
}
