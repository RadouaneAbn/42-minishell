/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:25:29 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:25:31 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_env(char *key)
{
	if (strmatch(key, "var"))
		return ("$var");
	else if (strmatch(key, "blank"))
		return ("              ");
	else if (strmatch(key, "quote"))
		return ("\"");
	else if (strmatch(key, "cwd"))
		return ("hey hey hey");
	else if (strmatch(key, "but"))
		return ("");
	else if (strmatch(key, "var1"))
		return ("\"\"");
	else if (strmatch(key, "var2"))
		return ("'");
	else if (strmatch(key, "star"))
		return ("*");
	return ("");
}
