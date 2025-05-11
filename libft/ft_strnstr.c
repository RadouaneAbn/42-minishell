/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:05:51 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/14 17:05:43 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_length;

	i = 0;
	if (len == 0 && big == NULL)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	little_length = ft_strlen(little);
	while (i + little_length <= len && *(big + i) != '\0')
	{
		if (ft_strncmp(big + i, little, little_length) == 0)
			return ((char *)big + i);
		i++;
	}
	return (0);
}
