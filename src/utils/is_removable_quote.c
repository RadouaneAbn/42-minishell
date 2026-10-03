/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_removable_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:27:16 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:27:17 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_removable_quote(char character, bool reset)
{
	static char		quote;
	static bool		quoted;

	if (!reset)
	{
		if (is_quote(character) && !quoted)
			quote = character;
		if (is_quote(character) && character == quote)
		{
			quoted = !quoted;
			return (true);
		}
	}
	else
	{
		quoted = false;
		quote = '\0';
	}
	return (false);
}
