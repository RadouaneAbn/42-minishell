/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 00:36:08 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/16 00:36:11 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*copy_string(char *src)
{
	char	*value;
	int		slen;

	if (src == NULL)
		return (NULL);
	slen = ft_strlen(src);
	value = gc_malloc_lvl(slen + 1, 0);
	ft_strlcpy(value, src, slen + 1);
	return (value);
}
