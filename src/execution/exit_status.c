/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radouane <radouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:48:37 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/15 17:29:28 by radouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*exit_code(void)
{
	static int	exit_code = 0;

	return (&exit_code);
}

int	get_exit_status(void)
{
	return (*exit_code());
}

void	set_exit_status(int status)
{
	*exit_code() = status;
}

void	store_child_exit_status(int status)
{
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		set_exit_status(128 + WTERMSIG(status));
	else
		set_exit_status(EXIT_FAILURE);
}
