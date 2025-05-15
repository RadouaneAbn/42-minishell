/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:26:18 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/24 20:27:00 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_new;
	unsigned char	*src_new;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_new = (unsigned char *)dst;
	src_new = (unsigned char *)src;
	while (n > 0)
	{
		*dst_new++ = *src_new++;
		n--;
	}
	return (dst);
}
