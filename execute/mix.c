/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:47 by mlektaib          #+#    #+#             */
/*   Updated: 2023/04/08 21:20:48 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	execute_redirect_heredoc(t_ast *node, t_env **env)
{
	int infile_fd = 0, outfile_fd = 1;
	int open_flags = 0, file_flags = 0;
	int pipefd[2];
	char *buffer = NULL;
	int end = 0;
	t_ast *cmd;
	if (node->type == ast_redirect_out)
		cmd = node->u_data.redirect_out.cmd;
	else if (node->type == ast_redirect_in)
		cmd = node->u_data.redirect_in.cmd;
	else if (node->type == ast_heredoc)
		cmd = node->u_data.heredoc.cmd;
	while (node)
	{
		if (node->type == ast_redirect_out)
		{
			if (node->u_data.redirect_out.tag == 1)
			{
				open_flags = O_WRONLY | O_CREAT | O_TRUNC;
				file_flags = 0633;
			}
			else if (node->u_data.redirect_out.tag == 2)
			{
				open_flags = O_WRONLY | O_CREAT | O_APPEND;
				file_flags = 0633;
			}
			outfile_fd = open(node->u_data.redirect_out.outfile, open_flags,
					file_flags);
			if (outfile_fd == -1)
			{
				perror(node->u_data.redirect_out.outfile);
				return (1);
			}
			node = node->u_data.redirect_out.next;
		}
		else if (node->type == ast_redirect_in)
		{
			open_flags = O_RDONLY;
			file_flags = 0633;
			infile_fd = open(node->u_data.redirect_in.infile, open_flags,
					file_flags);
			if (infile_fd == -1)
			{
				perror(node->u_data.redirect_in.infile);
				return (1);
			}
			node = node->u_data.redirect_in.next;
		}
		else if (node->type == ast_heredoc)
		{
			open_flags = O_WRONLY | O_CREAT | O_TRUNC;
			file_flags = 0633;
			infile_fd = open(node->u_data.heredoc.tmp, open_flags,file_flags);
			open_flags = O_WRONLY | O_CREAT | O_APPEND;
			infile_fd = open(node->u_data.heredoc.tmp, open_flags,file_flags);
			while (node && node->type == ast_heredoc)
			{
				if (node->u_data.heredoc.next)
				{
					if (!node->u_data.heredoc.next
						|| node->u_data.heredoc.next->type != ast_heredoc)
						end = 1;
				}
				buffer = NULL;
				buffer = readline("heredoc> ");
				if (!buffer)
					exit(1);
				if (strcmp(buffer, node->u_data.heredoc.delim) == 0)
				{
					node = node->u_data.heredoc.next;
					if (!node || node->type != ast_heredoc)
						continue ;
				}
				if (end)
				{
					write(infile_fd , buffer, strlen(buffer));
					write(infile_fd , "\n", 1);
				}
				free(buffer);
			}
			if (!node || node->type != ast_heredoc)
				continue ;
			node = node->u_data.heredoc.next;
		}
	}
	execute_simple_command_fd(cmd, env, infile_fd, outfile_fd);
	return (0);
}