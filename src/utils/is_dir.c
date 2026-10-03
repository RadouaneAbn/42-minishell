/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabounou <rabounou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:04:18 by rabounou          #+#    #+#             */
/*   Updated: 2025/07/10 16:04:19 by rabounou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/stat.h>

bool	is_dir(char *filename)
{
	struct stat	info;

	stat(filename, &info);
	return (S_ISDIR(info.st_mode));
}

bool	is_sym(char *filename)
{
	struct stat	info;

	lstat(filename, &info);
	return (S_ISLNK(info.st_mode));
}
