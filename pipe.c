/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:20:19 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/05 03:26:16 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	create_right_child(t_ast *node, int pipefd[2], int left_pid)
{
	int	right_pid;
	int	status;

	right_pid = fork();
	if (right_pid == -1)
		exit(1);
	else if (right_pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		execute_commands(node->u_data.operation.right);
		exit(0);
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(left_pid, NULL, 0);
		waitpid(right_pid, &status, 0);
		return (status);
	}
	return (status);
}

int	create_pipe(t_ast *node)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipefd) == -1)
		exit(1);
	left_pid = fork();
	if (left_pid == -1)
		exit(1);
	else if (left_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_commands(node->u_data.operation.left);
		exit(0);
	}
	else
		return (create_right_child(node, pipefd, left_pid));
}
