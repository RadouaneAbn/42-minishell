/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:28:27 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:28:28 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_strings(char **strings)
{
	size_t	index;

	if (strings == NULL)
	{
		printf("[NULL]\n");
		return ;
	}
	index = 0;
	while (strings[index])
	{
		printf("%zu: [%s]\n", index, strings[index]);
		index++;
	}
}
