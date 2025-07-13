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

long	convert_exist_status(char *arg)
{
	long	status;
	int		tmp;
	int		i;

	i = 0;
	status = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == FALSE)
			return (-1);
		tmp = arg[i] - '0';
		if (status * 10 + tmp < status)
			return (-1);
		status = status * 10 + tmp;
		i++;
	}
	return (status);
}
