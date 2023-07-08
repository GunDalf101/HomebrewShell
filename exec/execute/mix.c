/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:47 by mlektaib          #+#    #+#             */
/*   Updated: 2023/07/08 18:08:08 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

extern t_global	g_global;

void	execute_command_fd(t_ast *node, t_env **env, int infile_fd,
		int outfile_fd)
{
	if (infile_fd != STDIN_FILENO)
	{
		if (dup2(infile_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(infile_fd);
	}
	if (outfile_fd != STDOUT_FILENO)
	{
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
		close(outfile_fd);
	}
	execve(node->u_data.cmd.cmd, node->u_data.cmd.args, lst_to_env(*env));
	perror(node->u_data.cmd.cmd);
	exit(1);
}

t_ast	*get_cmd_node(t_ast *node)
{
	t_ast	*cmd;

	cmd = NULL;
	if (node->type == ast_redirect_out)
		cmd = node->u_data.redirect_out.cmd;
	else if (node->type == ast_redirect_in)
		cmd = node->u_data.redirect_in.cmd;
	else if (node->type == ast_heredoc)
		cmd = node->u_data.heredoc.cmd;
	else if (node->type == ast_subshell)
		cmd = node->u_data.subshell.child;
	return (cmd);
}

int	execute_subshell_fd(t_ast *node, t_env **env, int infile_fd, int outfile_fd)
{
	int	pid;
	int	subshell_status;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		dupping_fds(infile_fd, outfile_fd);
		subshell_status = execute_commands(node->u_data.subshell.child, env, 1);
		exit(subshell_status);
	}
	if (infile_fd != STDIN_FILENO)
		close(infile_fd);
	if (outfile_fd != STDOUT_FILENO)
		close(outfile_fd);
	return (get_subshell_exit_status(node, pid));
}

int	execute_redirect_heredoc(t_ast *node, t_env **env)
{
	t_fd	fd;
	t_ast	*cmd;

	cmd = NULL;
	fd_init(&fd);
	if (!fd.error)
		cmd = get_cmd_node(node);
	cmd = expand(cmd, env);
	while (node && g_global.run != 130)
		node = getting_fds_for_red(&fd, node, env);
	if (cmd && !fd.error && g_global.run != 130 && cmd && cmd->type == ast_cmd)
		return (execute_simple_command_fd(cmd, env, fd.infile_fd,
				fd.outfile_fd));
	else if (!fd.error && g_global.run != 130 && cmd
		&& cmd->type == ast_subshell)
		return (cmd && execute_subshell_fd(cmd, env, fd.infile_fd,
				fd.outfile_fd));
	else
		close_fds(&fd);
	if (g_global.run == 130)
		return (130);
	return (1);
}
