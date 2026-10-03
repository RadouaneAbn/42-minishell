/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:25:49 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 19:15:08 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_strings(char **strings)
{
	size_t	index;

	if (strings == NULL)
		return ;
	index = 0;
	while (strings[index])
	{
		gc_global_free(strings[index]);
		index++;
	}
	gc_global_free(strings);
}
