/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_dupping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:20:22 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 21:14:51 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	fd_init(t_fd *fd)
{
	fd->error = 0;
	fd->infile_fd = 0;
	fd->outfile_fd = 1;
}

t_ast	*open_heredoc_tmp(t_fd *fd, t_ast *node)
{
	if (fd->infile_fd != STDIN_FILENO)
		close(fd->infile_fd);
	fd->infile_fd = open(node->u_data.heredoc.tmp, O_RDONLY | O_EXCL, 0666);
	node = node->u_data.heredoc.next;
	return (node);
}

void	dupping_fds(int infile_fd, int outfile_fd)
{
	signal(SIGINT, command_sig);
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
}

void	close_fds(t_fd *fd)
{
	if (fd->infile_fd != STDIN_FILENO)
		close(fd->infile_fd);
	if (fd->outfile_fd != STDOUT_FILENO)
		close(fd->outfile_fd);
}