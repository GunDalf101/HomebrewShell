/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:21:46 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/16 02:20:43 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_ast	*getting_infile_fd(t_ast *node, t_fd *fd)
{
	int	open_flags;
	int	file_flags;

	open_flags = O_RDONLY;
	file_flags = 0633;
	if (fd->infile_fd != 0)
		close(fd->infile_fd);
	fd->infile_fd = open(node->u_data.redirect_in.infile, open_flags,
			file_flags);
	if (fd->infile_fd == -1)
	{
		perror(node->u_data.redirect_in.infile);
		fd->error = 1;
	}
	return (node->u_data.redirect_in.next);
}

t_ast	*create_red_files(t_ast *node, t_fd *fd)
{
	int	open_flags;
	int	file_flags;

	if (node->u_data.redirect_out.tag == 1)
		open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		open_flags = O_CREAT | O_WRONLY | O_APPEND;
	file_flags = 0633;
	if (fd->outfile_fd != 1)
		close(fd->outfile_fd);
	fd->outfile_fd = open(node->u_data.redirect_out.outfile, open_flags,
			file_flags);
	if (fd->outfile_fd == -1)
	{
		perror(node->u_data.redirect_out.outfile);
		fd->error = 1;
	}
	return (node->u_data.redirect_out.next);
}
