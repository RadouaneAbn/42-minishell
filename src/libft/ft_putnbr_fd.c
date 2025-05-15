/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:08:11 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/28 17:10:26 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	char			arr[12];
	char			arr2[12];
	unsigned int	nn;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (n == 0)
		arr[i++] = '0';
	else if (n < 0)
		arr2[j++] = '-';
	nn = (n < 0) * -n + (n > 0) * n;
	while (nn)
	{
		arr[i++] = nn % 10 + '0';
		nn /= 10;
	}
	while (i > 0)
		arr2[j++] = arr[--i];
	write(fd, arr2, j);
}
