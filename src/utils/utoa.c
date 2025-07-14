/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:29:49 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:29:50 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	utoa_length(size_t number)
{
	int	length;

	length = 1;
	while (number >= 10)
	{
		number = number / 10;
		length++;
	}
	return (length);
}

static void	utoa_fill(char *ptr, size_t number, int end, int start)
{
	while (end >= start)
	{
		*(ptr + end) = number % 10 + '0';
		number /= 10;
		end--;
	}
}

char	*utoa(size_t num)
{
	int		length;
	char	*ptr;
	int		start;

	start = 0;
	length = utoa_length(num);
	ptr = gc_malloc((length + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr[length] = '\0';
	utoa_fill(ptr, num, length - 1, start);
	return (ptr);
}
