/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_printlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:29:45 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:29:45 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_printlst(t_token_lst *token_lst)
{
	while (token_lst)
	{
		print_token(token_lst->token);
		token_lst = token_lst->next;
	}
}
