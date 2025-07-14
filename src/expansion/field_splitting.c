/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:44:59 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:46:19 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	has_unquoted_star(char *str, char *quote_mask, t_range range)
{
	size_t	index;

	index = 0;
	while (index < range.len)
	{
		if (!get_bit(quote_mask, range.start))
		{
			if (str[range.start] == '*'
				&& !quoted_char(quote_mask, range.start))
					return (true);
			index++;
		}
		range.start++;
	}
	return (false);
}

void	set_star_mask_bit(char character, size_t position,
	bool ch_is_quoted, char *star_mask_bits)
{
			if (character == '*' && !ch_is_quoted)
				set_mask_bit(star_mask_bits, position, 1);
			else
				set_mask_bit(star_mask_bits, position, 0);
}

void	fill_field_info(t_expansion info, t_range range,
	bool store_star_mask, char *star_mask)
{
	size_t	index;

	index = 0;
	while (index < range.len)
	{
		if (!get_bit(info.quote_mask, range.start))
		{
			if (store_star_mask)
				set_star_mask_bit(info.expand_str[range.start], index,
						quoted_char(info.quote_mask, range.start), star_mask);
			info.field[index] = info.expand_str[range.start];
			index++;
		}
		range.start++;
	}
	info.field[index] = '\0';
}

void	set_field_info(t_expansion info, t_range range)
{
	bool	store_star_mask;
	char	*star_mask;
	t_list	*new_node;

	store_star_mask = false;
	star_mask = NULL;
	if (has_unquoted_star(info.expand_str, info.quote_mask, range))
	{
			star_mask = gc_calloc(sizeof(char), get_byte_len(range.len));
			store_star_mask = true;
	}
	fill_field_info(info, range, store_star_mask, star_mask);
	new_node = ft_lstnew(star_mask);
	ft_lstadd_back(info.star_mask_list, new_node);
}
