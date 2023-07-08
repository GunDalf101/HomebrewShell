/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:25:39 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/08 18:06:25 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

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
	g_global.run = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		execute_command_fd(node, env, infile_fd, outfile_fd);
	else
		return (commnad_fd_es(pid, infile_fd, outfile_fd));
	return (1);
}

int	execute_simple_command(t_ast *node, t_env **env)
{
	int		status;
	pid_t	pid;

	if (ft_strlen(node->u_data.cmd.cmd) == 0)
		return (0);
	status = check_cmd(node, *env);
	if (status)
		return (status);
	g_global.run = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
		exec_cmd(node, env);
	else
		return (simple_command_es(pid));
	return (1);
}

int	execute_and(t_ast *node, t_env **env, int k)
{
	int	status;
	int	left_status;

	left_status = execute_commands(node->u_data.operation.left, env, k);
	if (left_status == 0)
		status = execute_commands(node->u_data.operation.right, env, k);
	else
		status = left_status;
	return (status);
}

int	execute_or(t_ast *node, t_env **env, int k)
{
	int	left_status;

	left_status = execute_commands(node->u_data.operation.left, env, k);
	if (left_status != 0 && left_status != 130)
		return (execute_commands(node->u_data.operation.right, env, k));
	return (left_status);
}

int	execute_commands(t_ast *node, t_env **env, int k)
{
	if (!node)
		return (0);
	if (node->type == ast_cmd)
		expand(node, env);
	set_imp_commands(node);
	if (!node)
		return (0);
	else if (node->type == ast_imp)
		return (execute_imp_commands(node, env, k));
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
		return (execute_and(node, env, k));
	else if (node->type == ast_or)
		return (execute_or(node, env, k));
	return (-1);
}
