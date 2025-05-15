/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:24:35 by rabounou          #+#    #+#             */
/*   Updated: 2024/10/24 20:24:42 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int main() {
	const char *s1 = "\x80";
	const char *s2 = "\x7F";
	size_t n = 1;
	printf("%d\n", strncmp(s1, s2, n));
	printf("%d\n", ft_strncmp(s1, s2, n));
}*/