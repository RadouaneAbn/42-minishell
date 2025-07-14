/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:37:07 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:38:44 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_byte_len(int len)
{
	int	size;

	size = len / 8 + ((len - (len / 8 * 8)) != 0);
	return (size);
}

void	shift_bits(char *quote_array, int size)
{
	int	index;
	int	rest;

	index = get_byte_len(size) - 1;
	if (size % 8 != 0)
	{
		rest = 8 - (size % 8);
		quote_array[index] = quote_array[index] << rest;
	}
}

void	set_mask_bit(char *quote_array, int size, char bit)
{
	int	byte_index;
	int	bit_index;

	byte_index = size / 8;
	bit_index = 8 - (size % 8) - 1;
	quote_array[byte_index] = quote_array[byte_index] | (bit << bit_index);
}

unsigned char	get_bit(char *quote_mask, size_t size)
{
	unsigned char	bit;
	size_t			char_index;
	size_t			bit_index;

	char_index = size / 8;
	bit_index = size % 8;
	bit = (unsigned char)(quote_mask[char_index] << bit_index) >> 7;
	return (bit);
}
