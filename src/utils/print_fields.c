/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:28:01 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:28:13 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_fields(char **fields, t_list *star_mask)
{
	size_t	index;

	index = 0;
	while (fields[index])
	{
		if (star_mask->content)
			print_bits(star_mask->content,
				get_byte_len(ft_strlen(fields[index])));
		star_mask = star_mask->next;
		index++;
	}
}
