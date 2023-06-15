/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:30:56 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 21:06:15 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	get_subshell_exit_status(t_ast *node, int pipefd[2], int pid)
{
	int		subshell_status;
	int		status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	read(pipefd[0], &subshell_status, sizeof(int));
	close(pipefd[0]);
	if (node->u_data.subshell.reparsethis)
		free(node->u_data.subshell.reparsethis);
	free(node);
	return (subshell_status);
}
int	execute_subshell(t_ast *node, t_env **env)
{
	int		pipefd[2];
	int		pid;
	int		subshell_status;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipefd[0]);
		subshell_status = execute_commands(node->u_data.subshell.child, env);
		write(pipefd[1], &subshell_status, sizeof(int));
		close(pipefd[1]);
		exit(subshell_status);
	}
	return (get_subshell_exit_status(node, pipefd, pid));
}
