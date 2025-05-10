/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:17 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/12 09:21:00 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	if (dest == NULL || src == NULL)
		return (NULL);
	dest_ptr = (unsigned char *)dest;
	src_ptr = (const unsigned char *)src;
	i = n;
	if (dest > src)
		while (i--)
			dest_ptr[i] = src_ptr[i];
	else
		ft_memcpy(dest_ptr, src_ptr, n);
	return (dest);
}
