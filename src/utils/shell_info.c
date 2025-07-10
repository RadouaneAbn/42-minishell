/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:04:23 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 19:26:31 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_info	*get_info(void)
{
	static t_info	*info;

	if (info == NULL)
	{
		info = gc_malloc_lvl(sizeof(t_info), 0);
		ft_bzero(info, sizeof(t_info));
	}
	return (info);
}
