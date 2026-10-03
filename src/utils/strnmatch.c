/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:29:35 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:29:36 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	strnmatch(const char *string_1, const char *string_2, size_t n)
{
	return (ft_strncmp(string_1, string_2, n) == 0);
}
