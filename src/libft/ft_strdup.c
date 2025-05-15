/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:53:20 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/24 13:53:21 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	strsize;
	char	*new_str;

	strsize = ft_strlen(s1) + 1;
	new_str = (char *) malloc(strsize * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, strsize);
	return (new_str);
}
