/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:34:04 by hsacr             #+#    #+#             */
/*   Updated: 2024/10/27 11:30:09 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_ptr;
	unsigned char		character;
	size_t				i;

	character = (unsigned char)c;
	s_ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*(s_ptr + i) == character)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
