/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:21:46 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/24 20:47:27 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_ast	*getting_infile_fd(t_ast *node, t_fd *fd, t_env *env)
{
	int	open_flags;
	int	file_flags;

	open_flags = O_RDONLY;
	file_flags = 0633;
	if (fd->infile_fd != 0)
		close(fd->infile_fd);
	node->u_data.redirect_in.infile = quotes_busters(
			node->u_data.redirect_in.infile, env, 1);
	node->u_data.redirect_in.infile = wild_redirection(node->u_data.redirect_in.infile);
	if(node->u_data.redirect_in.infile == NULL)
		{
			fd->error = 1;
			ft_putstr_fd("minishell: ambiguous redirect\n",2);
			return(NULL);
		}
	fd->infile_fd = open(node->u_data.redirect_in.infile, open_flags,
			file_flags);
	if (fd->infile_fd == -1)
	{
		perror(node->u_data.redirect_in.infile);
		fd->error = 1;
	}
	return (node->u_data.redirect_in.next);
}

t_ast	*create_red_files(t_ast *node, t_fd *fd, t_env *env)
{
	int	open_flags;

	if (fd->outfile_fd != 1)
		close(fd->outfile_fd);
	node->u_data.redirect_out.outfile = quotes_busters(
			node->u_data.redirect_out.outfile, env, 1);
	node->u_data.redirect_out.outfile = wild_redirection(node->u_data.redirect_out.outfile);
	if(node->u_data.redirect_out.outfile == NULL)
		{
			fd->error = 1;
			ft_putstr_fd("minishell: ambiguous redirect\n",2);
			return(NULL);
		}
	
	if (node->u_data.redirect_out.tag == 1)
		open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		open_flags = O_CREAT | O_WRONLY | O_APPEND;
	if (fd->outfile_fd != 1)
		close(fd->outfile_fd);
	fd->outfile_fd = open(node->u_data.redirect_out.outfile, open_flags,
			0633);
	if (fd->outfile_fd == -1)
	{
		perror(node->u_data.redirect_out.outfile);
		fd->error = 1;
	}
	return (node->u_data.redirect_out.next);
}
