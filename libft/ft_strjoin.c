/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:20:51 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/13 10:52:23 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;

	if (s1 == 0 && s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	if (s1 == 0)
		ft_strlcpy(ptr, s2, ft_strlen(s2) + 1);
	else if (s2 == 0)
		ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	else
	{
		ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
		ft_strlcat(ptr, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	}
	return (ptr);
}
