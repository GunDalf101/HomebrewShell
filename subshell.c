/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:30:56 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/05 03:31:35 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	get_subshell_exit_status(t_ast *node, int pipefd[2], int pid)
{
	int	read_result;
	int	subshell_status;
	int	subshell_exit_status;
	int	status;

	close(pipefd[1]);
	waitpid(pid, &subshell_status, 0);
	read_result = read(pipefd[0], &subshell_exit_status, sizeof(int));
	if (read_result == -1)
	{
		perror("read");
		exit(1);
	}
	status = subshell_exit_status;
	close(pipefd[0]);
	return (status);
}

int	execute_subshell(t_ast *node)
{
	int		pipefd[2];
	int		subshell_status;
	pid_t	pid;
	ssize_t	read_result;

	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDIN_FILENO);
		subshell_status = execute_commands(node->u_data.subshell.child);
		write(pipefd[1], &subshell_status, sizeof(int));
		exit(0);
	}
	else
		return (get_subshell_exit_status(node, pipefd, pid));
}
// close(pipefd[1]); line 51