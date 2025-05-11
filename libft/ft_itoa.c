/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:52:46 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/07 15:18:55 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_length(long number)
{
	int	length;

	length = 1;
	if (number < 0)
	{
		length++;
		number *= -1;
	}
	while (number >= 10)
	{
		number = number / 10;
		length++;
	}
	return (length);
}

static void	ft_itoa_allocate(char *ptr, long number, int end, int start)
{
	while (end >= start)
	{
		*(ptr + end) = number % 10 + '0';
		number /= 10;
		end--;
	}
}

char	*ft_itoa(int n)
{
	long	number;
	int		length;
	char	*ptr;
	int		start;

	start = 0;
	number = n;
	length = ft_itoa_length(number);
	ptr = (char *)malloc((length + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	*(ptr + length) = '\0';
	if (number < 0)
	{
		start = 1;
		*ptr = '-';
		number *= -1;
	}
	ft_itoa_allocate(ptr, number, length - 1, start);
	return (ptr);
}
