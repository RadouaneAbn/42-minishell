/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:11:33 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/03 18:39:55 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;

	ptr = (char *)s;
	if (ptr == 0)
		return (0);
	ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}
