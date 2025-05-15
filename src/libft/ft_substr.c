/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:44:04 by rabounou          #+#    #+#             */
/*   Updated: 2024/11/05 16:04:40 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;
	size_t	rlen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (start + len < slen)
		rlen = len + 1;
	else
		rlen = slen - start + 1;
	str = malloc(sizeof(char) * rlen);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, rlen);
	return (str);
}
