/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:50:11 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 00:22:12 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellexec.h"
#include "execute.h"

extern t_global	g_global;

int	check_last_heredoc(t_ast *node)
{
	if (node->u_data.heredoc.next || !node->u_data.heredoc.next)
	{
		if (!node->u_data.heredoc.next
			|| node->u_data.heredoc.next->type != ast_heredoc)
			return (1);
	}
	return (0);
}

void	write_heredoc_file(char *buffer, t_ast *node)
{
	int	infile_fd;

	infile_fd = open(node->u_data.heredoc.tmp, O_WRONLY | O_CREAT | O_APPEND,
			0777);
	if (infile_fd == -1)
	{
		perror(node->u_data.heredoc.tmp);
		return ;
	}
	g_global.run = infile_fd;
	if (write(infile_fd, buffer, strlen(buffer)) == -1)
	{
		perror("write");
		return ;
	}
	free(buffer);
	close(infile_fd);
}

void	heredoc_sig(int sig)
{
	(void)sig;
	g_global.run = 130;
	close(0);
}

void	open_tmp_file(t_ast *node, t_fd *fd)
{
	if (fd->infile_fd != 0)
		close(fd->infile_fd);
	fd->infile_fd = open(node->u_data.heredoc.tmp, O_WRONLY | O_CREAT | O_TRUNC,
			0777);
	if (fd->infile_fd == -1)
	{
		perror(node->u_data.heredoc.tmp);
		fd->error = 1;
		return ;
	}
	close(fd->infile_fd);
}
