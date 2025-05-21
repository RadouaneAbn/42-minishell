/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsacr <hsacr@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:29:27 by hsacr             #+#    #+#             */
/*   Updated: 2025/05/21 17:30:36 by hsacr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>

void	handle(int c)
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	handle_a(int c)
{
	write(1, "\n", 1);
	return ;
}

int main(void)
{
	signal(SIGINT, handle);
	while (1)
	{
		rl_outstream = stderr;
		char *line = readline("> ");
		char *ve[] = {line, NULL};
		int hey = fork();
		signal(SIGINT, handle_a);
		if (hey == 0)
		{
			execve(line, ve, NULL);
			perror("");
			printf("hey");
		}
		else
			wait(NULL);
	}
}
