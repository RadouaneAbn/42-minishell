/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:54:18 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/27 14:53:54 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;
	size_t			i;

	i = 0;
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && us1[i] == us2[i])
		i++;
	return (us1[i] - us2[i]);
}
