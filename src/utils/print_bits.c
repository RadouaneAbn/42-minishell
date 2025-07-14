/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:37:51 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:37:52 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_bit(unsigned char byte)
{
	int				index;
	unsigned char	bit;

	index = 0;
	while (index < 8)
	{
		bit = byte >> 7;
		byte = byte << 1;
		printf("%d ", bit);
		index++;
	}
}

void	print_bits(char *quote_array, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		print_bit(quote_array[index]);
		index++;
	}
}
