/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:52 by hsacr             #+#    #+#             */
/*   Updated: 2025/07/14 17:31:08 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tree(t_tree *tree, int n)
{
	int		i;
	char	*data_type[11];

	i = 0;
	data_type[T_COMPOUND_COMMAND] = "COMPOUND COMMAND";
	data_type[T_FILE_HERE_DOC] = "FILE_HERE_DOC";
	data_type[T_FILE_APPEND] = "FILE_APPEND";
	data_type[T_FILE_READ] = "FILE_READ";
	data_type[T_FILE_TRUNCATE] = "FILE_TRUNCATE";
	data_type[T_CMD_ARG] = "CMD ARG";
	data_type[T_AND] = "AND";
	data_type[T_OR] = "OR";
	data_type[T_COMMAND] = "COMMAND";
	data_type[T_SUBSHELL] = "SUBSHELL";
	data_type[T_PIPELINE] = "PIPELINE";
	while (tree)
	{
		i = 0;
		while (i < n)
		{
			i++;
			printf("\t");
		}
		printf("└──"GREEN"%s "BLUE"[%s]"RESET"\n",
			data_type[tree->data_type], (char *)tree->data);
		print_tree(tree->next, n + 1);
		tree = tree->sibling;
	}
}
