/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:28:34 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:29:10 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token(t_token token)
{
	char *types[] = {
		"AND",
		"OR",
		"HERE_DOC",
		"APPEND_OUT",
		"RED_IN",
		"RED_OUT",
		"PIPE",
		"L_PAREN",
		"R_PAREN",
		"WORD"
	};

	printf("token ["GREEN"%s"RESET"] token type: "BLUE"%s\n"RESET,
		token.lexeme, types[token.type]);
}
