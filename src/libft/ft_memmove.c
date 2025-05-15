/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:53:37 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/25 13:37:09 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*new_dst;
	unsigned char	*new_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	new_dst = (unsigned char *) dst;
	new_src = (unsigned char *) src;
	if (new_dst == new_src || len == 0)
		return (dst);
	if (new_dst < new_src)
	{
		while (len--)
			*new_dst++ = *new_src++;
	}
	else
	{
		new_dst += len - 1;
		new_src += len - 1;
		while (len--)
			*new_dst-- = *new_src--;
	}
	return (dst);
}
