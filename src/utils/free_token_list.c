/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:26:13 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 19:16:06 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_token_list(t_token_lst **token_lst)
{
	t_token_lst	*tmp;

	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		gc_global_free((*token_lst)->token.lexeme);
		gc_global_free(*token_lst);
		*token_lst = tmp;
	}
}
