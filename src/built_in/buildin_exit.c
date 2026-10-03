/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:37:16 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 15:37:17 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

bool	convert_to_long(char *arg, int *i, long *status)
{
	int		tmp;

	while (arg[*i] && !ft_isspace(arg[*i]))
	{
		if (ft_isdigit(arg[*i]) == FALSE)
			return (false);
		tmp = arg[*i] - '0';
		if (*status * 10 + tmp < *status)
			return (false);
		*status = *status * 10 + tmp;
		(*i)++;
	}
	return (true);
}

bool	convert_exist_status(char *arg, long *status)
{
	int		sign;
	int		i;

	i = 0;
	*status = 0;
	sign = 1;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(arg[i]))
		return (false);
	if (convert_to_long(arg, &i, status) == false)
		return (false);
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i])
		return (false);
	*status *= sign;
	return (true);
}
