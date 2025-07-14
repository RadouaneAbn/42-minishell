/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_blank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:29:25 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:29:26 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	str_blank(char *str)
{
	size_t	index;
	size_t	space_count;

	index = 0;
	space_count = 0;
	while (str[index])
	{
		if (char_in_set(str[index], "\t\n "))
			space_count++;
		index++;
	}
	return (space_count == index);
}
