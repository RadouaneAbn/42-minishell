/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:18:09 by hsacr             #+#    #+#             */
/*   Updated: 2024/11/07 15:18:34 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	int	alpha_upp;
	int	alpha_low;
	int	digit;

	digit = (c >= '0' && c <= '9');
	alpha_upp = (c <= 'Z' && c >= 'A');
	alpha_low = (c <= 'z' && c >= 'a');
	return (alpha_upp | alpha_low | digit);
}
