/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:27:09 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/24 20:27:44 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		target;
	const unsigned char	*new_s;
	size_t				i;

	target = (unsigned char) c;
	new_s = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (new_s[i] == target)
			return ((void *)(new_s + i));
		i++;
	}
	return (NULL);
}
