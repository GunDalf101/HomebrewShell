/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:47 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/09 06:02:51 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	fd_init(t_fd *fd)
{
	fd->error = 0;
	fd->infile_fd = 0;
	fd->error = 0;
}

void	execute_command_fd(t_ast *node, t_env **env, int infile_fd,
		int outfile_fd)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(infile_fd);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(outfile_fd);
	execve(node->u_data.cmd.cmd, node->u_data.cmd.args, lst_to_env(*env));
	perror(node->u_data.cmd.cmd);
	exit(1);
}

t_ast	*get_cmd_node(t_ast *node)
{
	t_ast	*cmd;

	if (node->type == ast_redirect_out)
		cmd = node->u_data.redirect_out.cmd;
	else if (node->type == ast_redirect_in)
		cmd = node->u_data.redirect_in.cmd;
	else if (node->type == ast_heredoc)
		cmd = node->u_data.heredoc.cmd;
	return (cmd);
}

int	execute_redirect_heredoc(t_ast *node, t_env **env)
{
	t_fd	fd;
	t_ast	*cmd;

	fd_init(&fd);
	cmd = get_cmd_node(node);
	while (node)
	{
		if (fd.infile_fd == -1)
			fd.error = 1;
		if (node->type == ast_redirect_out)
			node = create_red_files(node, &fd.outfile_fd);
		else if (node->type == ast_redirect_in)
			node = getting_infile_fd(node, &fd.infile_fd);
		else if (node->type == ast_heredoc)
		{
			open_tmp_file(node, &fd.infile_fd);
			node = heredoc_handler(node, fd.infile_fd);
			if (!node || node->type != ast_heredoc)
				continue ;
			node = node->u_data.heredoc.next;
		}
	}
	if (!fd.error)
		execute_simple_command_fd(cmd, env, fd.infile_fd, fd.outfile_fd);
	return (0);
}
