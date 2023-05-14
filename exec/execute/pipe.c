/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:20:19 by mlektaib          #+#    #+#             */
/*   Updated: 2023/05/14 21:01:52 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	create_right_child(t_ast *node, int pipefd[2], int left_pid, t_env **env)
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
		return (execute_commands(node->u_data.operation.right, env));
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(left_pid, NULL, 0);
		waitpid(right_pid, &status, 0);
		return (status);
	}
}
		// if (node->u_data.operation.right->type == ast_exit)
		// 	exit(25);

int	create_pipe(t_ast *node, t_env **env)
{
	int		pipefd[2];
	pid_t	left_pid;
	// pid_t	right_pid;

	if (pipe(pipefd) == -1)
		exit(1);
	left_pid = fork();
	if (left_pid == -1)
		exit(1);
	else if (left_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_commands(node->u_data.operation.left, env);
		return (0);
	}
	else
		return (create_right_child(node, pipefd, left_pid, env));
}
