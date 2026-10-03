/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_strings_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:27:06 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:27:07 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	get_strings_len(char **strings)
{
	size_t	len;

	if (strings == NULL)
		return (0);
	len = 0;
	while (strings[len])
		len++;
	return (len);
}
