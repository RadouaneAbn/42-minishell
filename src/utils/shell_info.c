/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:04:23 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 16:04:24 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_info	*get_info(void)
{
	static t_info	*info;

	if (info == NULL)
	{
		info = malloc(sizeof(t_info));
		ft_bzero(info, sizeof(t_info));
	}
	return (info);
}
