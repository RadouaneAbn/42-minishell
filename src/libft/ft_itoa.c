/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:05:30 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/28 17:07:07 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*itoa_helper(char *arr, int size)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *) malloc((size + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (--size >= 0)
		s[i++] = arr[size];
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	char			arr[12];
	char			*new_string;
	int				i;
	int				is_signed;
	unsigned int	nn;

	i = 0;
	is_signed = (n < 0);
	if (n == 0)
		arr[i++] = '0';
	nn = (n < 0) * -n + (n > 0) * n;
	while (nn)
	{
		arr[i++] = nn % 10 + '0';
		nn /= 10;
	}
	if (is_signed)
		arr[i++] = '-';
	arr[i] = '\0';
	new_string = itoa_helper(arr, i);
	return (new_string);
}
