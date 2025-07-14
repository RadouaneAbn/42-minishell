/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_in_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:25:20 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:25:21 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	char_in_set(char c, char *set)
{
	size_t	index;

	index = 0;
	while (set[index])
	{
		if (c == set[index])
			return (true);
		index++;
	}
	return (false);
}
