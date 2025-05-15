/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:23:26 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/25 15:23:44 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen1;
	size_t	slen2;
	size_t	total_len;
	char	*new_str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	total_len = slen1 + slen2 + 1;
	new_str = (char *) malloc(total_len * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, total_len);
	ft_strlcpy(new_str + slen1, s2, total_len);
	return (new_str);
}
