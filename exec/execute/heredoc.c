/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlektaib <mlektaib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:20:44 by mlektaib          #+#    #+#             */
/*   Updated: 2023/06/22 16:56:43 by mlektaib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellexec.h"
#include "execute.h"

extern t_global	g_global;

int	handle_dupstdin_and_sig(void)
{
	int	dupstdin;

	dupstdin = dup(0);
	if (dupstdin == -1)
	{
		perror("dup");
		return (-1);
	}
	signal(SIGINT, heredoc_sig);
	return (dupstdin);
}

void	write_in_heredoc_file(char *totalbuffer, t_ast *tmp, t_fd *fd)
{
	write_heredoc_file(totalbuffer, tmp);
	fd->infile_fd = open(tmp->u_data.heredoc.tmp, O_RDWR | O_EXCL, 0600);
	if (fd->infile_fd == -1)
	{
		perror(tmp->u_data.heredoc.tmp);
		fd->error = 1;
	}
}

void	redup_stdin(t_fd *fd)
{
	if (g_global.run == 130)
	{
		if (dup2(fd->dupstdin, 0) == -1)
		{
			perror("dup2");
			fd->error = 1;
		}
	}
}

t_ast	*heredoc_handler(t_ast *node, t_fd *fd,t_env **env)
{
	char	*totalbuffer;
	t_ast	*tmp;

	fd->dupstdin = handle_dupstdin_and_sig();
	tmp = node;
	g_global.run = 1;
	totalbuffer = ft_strdup("");
	node = read_heredoc(node, fd, &totalbuffer,env);
	if (g_global.run != 130)
		write_in_heredoc_file(totalbuffer, tmp, fd);
	else 
	{
		fd->error = 1;
		free(totalbuffer);
		close(fd->infile_fd);
	}
	signal(SIGINT, signal_hand);
	return (node);
}
