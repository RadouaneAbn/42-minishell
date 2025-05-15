/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:42:16 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/23 20:42:18 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dest && !dstsize)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dstsize <= dest_len)
		return (src_len + dstsize);
	ft_strlcpy(dest + dest_len, src, dstsize - dest_len);
	return (dest_len + src_len);
}
