/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:18:03 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/13 11:36:05 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_atoi(const char *nptr)
{
	unsigned long long	atoi_result;
	int					atoi_result_sign;

	if (nptr == 0)
		return (0);
	atoi_result = 0;
	atoi_result_sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			atoi_result_sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		atoi_result = atoi_result * 10 + (*(nptr++) - '0');
		if (atoi_result > LONG_MAX || (atoi_result + 1 > LONG_MAX
				&& atoi_result_sign < 0))
			return ((atoi_result_sign < 0) - 1);
	}
	return (atoi_result * atoi_result_sign);
}
