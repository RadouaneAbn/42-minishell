/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:18:47 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/05 14:39:26 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	if (s == 0 || f == 0)
		return (0);
	ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (*(s + i) != '\0')
	{
		*(ptr + i) = f(i, *(s + i));
		i++;
	}
	*(ptr + i) = 0;
	return (ptr);
}
