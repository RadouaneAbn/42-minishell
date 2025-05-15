/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:12:45 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/27 18:12:48 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	slen;
	char			*new_str;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	slen = ft_strlen(s);
	new_str = (char *) malloc((slen + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
