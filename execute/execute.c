/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:25:39 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/11 01:34:25 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
extern int run;


int	execute_simple_command_fd(t_ast *node, t_env **env, int infile_fd,
		int outfile_fd)
{
	int		status;
	pid_t	pid;

	
	if (node == NULL)
		return (0);
	status = check_cmd(node, *env);
	if (status)
		return (status);
	run = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		execute_command_fd(node, env, infile_fd, outfile_fd);
	else
	{
		waitpid(pid, &status, 0);
		run = 0;
		return (status);
	}
	return (1);
}

int	execute_simple_command(t_ast *node, t_env **env)
{
	int		status;
	pid_t	pid;

	status = check_cmd(node, *env);
	if (status)
		return (status);
	run = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		// signal(SIGINT, SIG_DFL);
		execve(node->u_data.cmd.cmd, node->u_data.cmd.args, lst_to_env(*env));
		perror(node->u_data.cmd.cmd);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		run = 0;
		return (status);
	}
}

int	execute_and(t_ast *node, t_env **env)
{
	int	status;
	int	left_status;

	left_status = execute_commands(node->u_data.operation.left, env);
	if (left_status == 0)
	{
		status = execute_commands(node->u_data.operation.right, env);
	}
	else
		status = left_status;
	return (status);
}

int	execute_or(t_ast *node, t_env **env)
{
	int	status;
	int	left_status;

	left_status = execute_commands(node->u_data.operation.left, env);
	if (left_status != 0)
		return (execute_commands(node->u_data.operation.right, env));
	return (25);
}

int	execute_commands(t_ast *node, t_env **env)
{
	if (!node)
		return (0);
	if (node->type == ast_exit)
		exit(25);
	else if (node->type == ast_imp)
		return (execute_imp_commands(node, env));
	else if (node->type == ast_cmd)
		return (execute_simple_command(node, env));
	else if (node->type == ast_pipe)
		return (create_pipe(node, env));
	else if (node->type == ast_redirect_in || node->type == ast_redirect_out
		|| node->type == ast_heredoc)
		return (execute_redirect_heredoc(node, env));
	else if (node->type == ast_subshell)
		return (execute_subshell(node, env));
	else if (node->type == ast_and)
		return (execute_and(node, env));
	else if (node->type == ast_or)
		return (execute_or(node, env));
	return (-1);
}
